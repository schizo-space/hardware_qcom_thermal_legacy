# QTI Thermal for legacy devices

- Clone the repository in hardware/qcom/thermal-legacy
- Add package on your device.mk:

```makefile
# Thermal
PRODUCT_PACKAGES += \
    android.hardware.thermal@2.0-service.qti.legacy
```

Also you need to address some SELinux denials in **sepolicy/vendor/file_contexts**:

    # Thermal
    /(vendor|system/vendor)/bin/hw/android\.hardware\.thermal@2\.0-service\.qti\.legacy   u:object_r:hal_thermal_default_exec:s0

Also you need to address some SELinux denials in **sepolicy/vendor/hal_thermal_default.te**:

    # This is required to access proc stat for fetching CPU usage
    allow hal_thermal_default proc_stat:file { getattr open read };

    # This is required for thermal sysfs access
    allow hal_thermal_default sysfs_thermal:file w_file_perms;

    # netlink access
    allow hal_thermal_default self:netlink_kobject_uevent_socket create_socket_perms_no_ioctl;
