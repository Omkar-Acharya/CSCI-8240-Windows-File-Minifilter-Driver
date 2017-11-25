#include "SystemFilter.h"

NTSTATUS FsFilterDispatchPassThrough(
	__in PDEVICE_OBJECT DeviceObject,
	__in PIRP           Irp
)
{
	PFSFILTER_DEVICE_EXTENSION pDevExt = (PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(Irp);
	return IoCallDriver(pDevExt->AttachedToDeviceObject, Irp);
}

NTSTATUS FsFilterDispatchCreate(
	__in PDEVICE_OBJECT DeviceObject,
	__in PIRP           Irp
)
{
	PFILE_OBJECT pFileObject = IoGetCurrentIrpStackLocation(Irp)->FileObject;

	DbgPrint("%wZ\n", &pFileObject->FileName);

	return FsFilterDispatchPassThrough(DeviceObject, Irp);
}