#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

PFLT_FILTER MyminiFilterHandle;
NTSTATUS MyMiniUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags);
FLT_POSTOP_CALLBACK_STATUS MyPostCreate(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext, FLT_POST_OPERATION_FLAGS Flags);
FLT_PREOP_CALLBACK_STATUS MyPreCreate(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext);
FLT_PREOP_CALLBACK_STATUS MyPreWrite(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext);
FLT_PREOP_CALLBACK_STATUS MyPreRead(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext);



const FLT_OPERATION_REGISTRATION Callbacks[] = {
	{ IRP_MJ_CREATE, 0, MyPreCreate, MyPostCreate },
	{ IRP_MJ_READ, 0, MyPreRead, NULL },
	{ IRP_MJ_WRITE, 0, MyPreWrite, NULL },
	{ IRP_MJ_OPERATION_END }
};

const FLT_REGISTRATION FilterRegistration = {
	sizeof(FLT_REGISTRATION),
	FLT_REGISTRATION_VERSION,
	0,
	NULL,
	Callbacks,
	MyMiniUnload,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

/*This is the unload routine for this miniFilter driver*/
NTSTATUS MyMiniUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags)
{
	KdPrint(("My Driver is Unloaded\r\n"));
	FltUnregisterFilter(MyminiFilterHandle);
	return STATUS_SUCCESS;
}

/*This is post create operation method for MJ_CREATE*/
FLT_POSTOP_CALLBACK_STATUS MyPostCreate(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext, FLT_POST_OPERATION_FLAGS Flags){
	KdPrint(("My Post Create is running \r\n"));
	return FLT_POSTOP_FINISHED_PROCESSING;
}

/*This is pre create operation method for MJ_CREATE*/
FLT_PREOP_CALLBACK_STATUS MyPreCreate(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext){
	PFLT_FILE_NAME_INFORMATION FileInfo;
	NTSTATUS status;
	WCHAR Name[900] = { 0 };

	status = FltGetFileNameInformation(DataInfo, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &FileInfo);
	
	if (NT_SUCCESS(status)) {
		status = FltParseFileNameInformation(FileInfo);

		if (NT_SUCCESS(status)) {
			if (FileInfo->Name.MaximumLength < 960) {
				RtlCopyMemory(Name, FileInfo->Name.Buffer, FileInfo->Name.MaximumLength);
				KdPrint(("Created File is: %ws \r\n", Name));
			}
		}
		FltReleaseFileNameInformation(FileInfo);
	}
	return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

/*This is pre write operation method for MJ_CREATE*/
FLT_PREOP_CALLBACK_STATUS MyPreWrite(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext) {
	PFLT_FILE_NAME_INFORMATION FileInfo;
	NTSTATUS status;
	WCHAR Name[900] = { 0 };

	status = FltGetFileNameInformation(DataInfo, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &FileInfo);

	if (NT_SUCCESS(status)) {
		status = FltParseFileNameInformation(FileInfo);

		if (NT_SUCCESS(status)) {
			if (FileInfo->Name.MaximumLength < 960) {
				RtlCopyMemory(Name, FileInfo->Name.Buffer, FileInfo->Name.MaximumLength);
				KdPrint(("This File is Written: %ws \r\n", Name));
			}
		}
		FltReleaseFileNameInformation(FileInfo);
	}
	return FLT_PREOP_SUCCESS_NO_CALLBACK;
}


/*This is pre read operation method for MJ_CREATE*/
FLT_PREOP_CALLBACK_STATUS MyPreRead(PFLT_CALLBACK_DATA DataInfo, PCFLT_RELATED_OBJECTS FltObjects, PVOID* CompletionContext) {
	PFLT_FILE_NAME_INFORMATION FileInfo;
	NTSTATUS status;
	WCHAR Name[900] = { 0 };

	status = FltGetFileNameInformation(DataInfo, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &FileInfo);

	if (NT_SUCCESS(status)) {
		status = FltParseFileNameInformation(FileInfo);

		if (NT_SUCCESS(status)) {
			if (FileInfo->Name.MaximumLength < 960) {
				RtlCopyMemory(Name, FileInfo->Name.Buffer, FileInfo->Name.MaximumLength);
				KdPrint(("This File is Read: %ws \r\n", Name));
			}
		}
		FltReleaseFileNameInformation(FileInfo);
	}
	return FLT_PREOP_SUCCESS_NO_CALLBACK;
}

/*This is the initialization routine for this miniFilter driver.This
registers with FltMgr and initializes all global data structures. Entry point for the driver*/
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject,	_In_ PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;

	KdPrint(("Entered DriverEntry method for this driver\n"));

	status = FltRegisterFilter(DriverObject, &FilterRegistration, &MyminiFilterHandle);

	if (NT_SUCCESS(status)) {

		status = FltStartFiltering(MyminiFilterHandle);

		if (!NT_SUCCESS(status)) {

			FltUnregisterFilter(MyminiFilterHandle);
		}
	}

	return status;
}
