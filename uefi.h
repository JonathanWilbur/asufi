// typedef struct EFI_BOOT_SERVICES {
//     EFI_TABLE_HEADER Hdr; // 24 bytes
//     EFI_RAISE_TPL RaiseTPL; // 8 bytes
//     EFI_RESTORE_TPL RestoreTPL; // 8 bytes
//     EFI_ALLOCATE_PAGES AllocatePages; // 8 bytes
//     EFI_FREE_PAGES FreePages; // 8 bytes
//     EFI_GET_MEMORY_MAP GetMemoryMap; // 8 bytes
//     EFI_ALLOCATE_POOL AllocatePool; // 8 bytes
//     EFI_FREE_POOL FreePool; // 8 bytes
//     EFI_CREATE_EVENT CreateEvent; // 8 bytes
//     EFI_SET_TIMER SetTimer; // 8 bytes
//     EFI_WAIT_FOR_EVENT WaitForEvent; // 8 bytes
//     EFI_SIGNAL_EVENT SignalEvent; // 8 bytes
//     EFI_CLOSE_EVENT CloseEvent; // 8 bytes
//     EFI_CHECK_EVENT CheckEvent; // 8 bytes
//     EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface; // 8 bytes
//     EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // 8 bytes
//     EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // 8 bytes
//     EFI_HANDLE_PROTOCOL HandleProtocol; // 8 bytes, offset=152
//     VOID *Reserved;
//     EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
//     EFI_LOCATE_HANDLE LocateHandle;
//     EFI_LOCATE_DEVICE_PATH LocateDevicePath;
//     EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;
//     EFI_IMAGE_LOAD LoadImage;
//     EFI_IMAGE_START StartImage;
//     EFI_EXIT Exit;
//     EFI_IMAGE_UNLOAD UnloadImage;
//     EFI_EXIT_BOOT_SERVICES ExitBootServices;
//     EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
//     EFI_STALL Stall;
//     EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;
//     EFI_CONNECT_CONTROLLER ConnectController;
//     EFI_DISCONNECT_CONTROLLER DisconnectController;
//     EFI_OPEN_PROTOCOL OpenProtocol;
//     EFI_CLOSE_PROTOCOL CloseProtocol;
//     EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;
//     EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
//     EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
//     EFI_LOCATE_PROTOCOL LocateProtocol;
//     EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
//     EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;
//     EFI_CALCULATE_CRC32 CalculateCrc32;
//     EFI_COPY_MEM CopyMem;
//     EFI_SET_MEM SetMem;
//     EFI_CREATE_EVENT_EX CreateEventEx;
// } EFI_BOOT_SERVICES;

// typedef EFI_STATUS (EFIAPI *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(IN struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, OUT EFI_FILE_PROTOCOL **Root);

// typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
//     UINT64 Revision;
//     EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
// } EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

// typedef struct EFI_FILE_PROTOCOL {
//     UINT64 Revision;
//     EFI_FILE_OPEN Open;
//     EFI_FILE_CLOSE Close;
//     EFI_FILE_DELETE Delete;
//     EFI_FILE_READ Read;
//     EFI_FILE_WRITE Write;
//     EFI_FILE_GET_POSITION GetPosition;
//     EFI_FILE_SET_POSITION SetPosition;
//     EFI_FILE_GET_INFO GetInfo;
//     EFI_FILE_SET_INFO SetInfo;
//     EFI_FILE_FLUSH Flush;
//     EFI_FILE_OPEN_EX OpenEx;
//     EFI_FILE_READ_EX ReadEx;
//     EFI_FILE_WRITE_EX WriteEx;
//     EFI_FILE_FLUSH_EX FlushEx;
// } EFI_FILE_PROTOCOL;

// typedef struct EFI_SYSTEM_TABLE {
//       EFI_TABLE_HEADER Hdr;
//       CHAR16 *FirmwareVendor;
//       UINT32 FirmwareRevision;
//       EFI_HANDLE ConsoleInHandle;
//       EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
//       EFI_HANDLE ConsoleOutHandle;
//       EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut; // Offset: +0x40
//       EFI_HANDLE StandardErrorHandle; // Offset: +0x48
//       EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr; // Offset: +0x50
//       EFI_RUNTIME_SERVICES *RuntimeServices; // Offset: +0x58
//       EFI_BOOT_SERVICES *BootServices;
//       UINTN NumberOfTableEntries;
//       EFI_CONFIGURATION_TABLE *ConfigurationTable;
// } EFI_SYSTEM_TABLE;
