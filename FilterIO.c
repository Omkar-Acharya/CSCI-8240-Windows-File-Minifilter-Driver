#include "SystemFilter.h"

/////////////////////////////////////////////////////////////////////////////
// Fast-IO Handlers

BOOLEAN CheckFilterFastIO(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in BOOLEAN            Wait,
	__in ULONG              LockKey,
	__in BOOLEAN            CheckForReadOperation,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	//
	//  Pass through logic for this type of Fast I/O
	//

	PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
	PFAST_IO_DISPATCH fastIoDispatch = nextDeviceObject->DriverObject->FastIoDispatch;

	if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoCheckIfPossible))
	{
		return (fastIoDispatch->FastIoCheckIfPossible)(
			FileObject,
			FileOffset,
			Length,
			Wait,
			LockKey,
			CheckForReadOperation,
			IoStatus,
			nextDeviceObject);
	}

	return FALSE;
}

BOOLEAN ReadFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in BOOLEAN            Wait,
	__in ULONG              LockKey,
	__out PVOID             Buffer,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	//
	//  Pass through logic for this type of Fast I/O
	//

	PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
	PFAST_IO_DISPATCH fastIoDispatch = nextDeviceObject->DriverObject->FastIoDispatch;

	if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoRead))
	{
		return (fastIoDispatch->FastIoRead)(
			FileObject,
			FileOffset,
			Length,
			Wait,
			LockKey,
			Buffer,
			IoStatus,
			nextDeviceObject);
	}

	return FALSE;
}

BOOLEAN WriteFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in BOOLEAN            Wait,
	__in ULONG              LockKey,
	__in PVOID              Buffer,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	//
	//  Pass through logic for this type of Fast I/O
	//

	PDEVICE_OBJECT    nextDeviceObject = ((PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject;
	PFAST_IO_DISPATCH fastIoDispatch = nextDeviceObject->DriverObject->FastIoDispatch;

	if (VALID_FAST_IO_DISPATCH_HANDLER(fastIoDispatch, FastIoWrite))
	{
		return (fastIoDispatch->FastIoWrite)(
			FileObject,
			FileOffset,
			Length,
			Wait,
			LockKey,
			Buffer,
			IoStatus,
			nextDeviceObject);
	}

	return FALSE;
}

BOOLEAN BasicQueryInfo(
	__in PFILE_OBJECT       FileObject,
	__in BOOLEAN            Wait,
	__out PFILE_BASIC_INFORMATION Buffer,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN StandardQueryInfo(
	__in PFILE_OBJECT       FileObject,
	__in BOOLEAN            Wait,
	__out PFILE_STANDARD_INFORMATION Buffer,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN LockFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in PLARGE_INTEGER     Length,
	__in PEPROCESS          ProcessId,
	__in ULONG              Key,
	__in BOOLEAN            FailImmediately,
	__in BOOLEAN            ExclusiveLock,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN UnlockSingleFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in PLARGE_INTEGER     Length,
	__in PEPROCESS          ProcessId,
	__in ULONG              Key,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN UnlockAllFilter(
	__in PFILE_OBJECT       FileObject,
	__in PEPROCESS          ProcessId,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN UnlockAllByKeyFilter(
	__in PFILE_OBJECT       FileObject,
	__in PVOID              ProcessId,
	__in ULONG              Key,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN DeviceControlFilter(
	__in PFILE_OBJECT       FileObject,
	__in BOOLEAN            Wait,
	__in_opt PVOID          InputBuffer,
	__in ULONG              InputBufferLength,
	__out_opt PVOID         OutputBuffer,
	__in ULONG              OutputBufferLength,
	__in ULONG              IoControlCode,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

VOID DetachDeviceFilter(
	__in PDEVICE_OBJECT     SourceDevice,
	__in PDEVICE_OBJECT     TargetDevice
)
{}

BOOLEAN QueryNetworkOpenInfoFilter(
	__in PFILE_OBJECT       FileObject,
	__in BOOLEAN            Wait,
	__out PFILE_NETWORK_OPEN_INFORMATION Buffer,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN MdlReadFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in ULONG              LockKey,
	__out PMDL*             MdlChain,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN MdlReadCompleteFilter(
	__in PFILE_OBJECT       FileObject,
	__in PMDL               MdlChain,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN PrepareMdlWriteFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in ULONG              LockKey,
	__out PMDL*             MdlChain,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN MdlWriteCompleteFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in PMDL               MdlChain,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN ReadCompressedFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in ULONG              LockKey,
	__out PVOID             Buffer,
	__out PMDL*             MdlChain,
	__out PIO_STATUS_BLOCK  IoStatus,
	__out struct _COMPRESSED_DATA_INFO* CompressedDataInfo,
	__in ULONG              CompressedDataInfoLength,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN WriteCompressedFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in ULONG              Length,
	__in ULONG              LockKey,
	__in PVOID              Buffer,
	__out PMDL*             MdlChain,
	__out PIO_STATUS_BLOCK  IoStatus,
	__in struct _COMPRESSED_DATA_INFO*  CompressedDataInfo,
	__in ULONG              CompressedDataInfoLength,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN ReadCompleteCompressedFilter(
	__in PFILE_OBJECT       FileObject,
	__in PMDL               MdlChain,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN WriteCompleteCompressedFilter(
	__in PFILE_OBJECT       FileObject,
	__in PLARGE_INTEGER     FileOffset,
	__in PMDL               MdlChain,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}

BOOLEAN QueryOpenFilter(
	__in PIRP               Irp,
	__out PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
	__in PDEVICE_OBJECT     DeviceObject
)
{
	return FALSE;
}