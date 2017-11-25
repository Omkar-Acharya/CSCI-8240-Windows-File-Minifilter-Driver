#include "SystemFilter.h"

VOID FsFilterUnload(																//Declaring UnloadMethod
	__in PDRIVER_OBJECT DriverObject
);

PDRIVER_OBJECT g_FileDriverObject = NULL;

FAST_IO_DISPATCH g_fastIoDispatch =													//Global Method for Fast-io
{
	sizeof(FAST_IO_DISPATCH),
	CheckFilterFastIO,
	ReadFilter,
	WriteFilter,
	BasicQueryInfo,
	StandardQueryInfo,
	LockFilter,
	UnlockSingleFilter,
	UnlockAllFilter,
	UnlockAllByKeyFilter,
	DeviceControlFilter,
	NULL,
	NULL,
	DetachDeviceFilter,
	QueryNetworkOpenInfoFilter,
	NULL,
	MdlReadFilter,
	MdlReadCompleteFilter,
	PrepareMdlWriteFilter,
	MdlWriteCompleteFilter,
	ReadCompressedFilter,
	WriteCompressedFilter,
	ReadCompleteCompressedFilter,
	WriteCompleteCompressedFilter,
	QueryOpenFilter,
	NULL,
	NULL,
	NULL,
};

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) //main- Entry Point of the Driver
{
	NTSTATUS status = STATUS_SUCCESS;

	ULONG    i = 0;

	g_FileDriverObject = DriverObject;												//Storing the Driver Object

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; ++i)
	{
		DriverObject->MajorFunction[i] = FsFilterDispatchPassThrough;
	}
	DriverObject->MajorFunction[IRP_MJ_CREATE] = FsFilterDispatchCreate;

	DriverObject->FastIoDispatch = &g_fastIoDispatch;								//Set fast-io Dispatch table

	status = IoRegisterFsRegistrationChange(DriverObject, FsFilterNotificationCallback);	//Call-back routine for file system change
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	DriverObject->DriverUnload = FsFilterUnload;									//Driver Unload Method
	return STATUS_SUCCESS;
}

VOID FsFilterUnload(__in PDRIVER_OBJECT DriverObject)
{
	ULONG           numDevices = 0;
	ULONG           i = 0;
	LARGE_INTEGER   interval;
	PDEVICE_OBJECT  devList[DEVOBJ_LIST_SIZE];

	interval.QuadPart = (5 * DELAY_ONE_SECOND);

	IoUnregisterFsRegistrationChange(DriverObject, FsFilterNotificationCallback);	//Unregistered callback routine for file system changes

	for (;;)
	{
		IoEnumerateDeviceObjectList(
			DriverObject,
			devList,
			sizeof(devList),
			&numDevices);
		if (0 == numDevices)
		{
			break;
		}
		numDevices = min(numDevices, RTL_NUMBER_OF(devList));
		for (i = 0; i < numDevices; ++i)
		{
			FsFilterDetachFromDevice(devList[i]);
			ObDereferenceObject(devList[i]);
		}

		KeDelayExecutionThread(KernelMode, FALSE, &interval);
	}
}

BOOLEAN FsFilterIsMyDeviceObject(__in PDEVICE_OBJECT DeviceObject)
{
	return DeviceObject->DriverObject == g_FileDriverObject;
}