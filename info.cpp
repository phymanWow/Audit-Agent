#include "info.h"
#include "architecture.h"
#include "linuxnetwork.h"
#include "macnetwork.h"
#include "linuxasset.h"
#include "macasset.h"
#include "linuxcpu.h"
#include "maccpu.h"
#include "linuxharddrive.h"
#include "macharddrive.h"
#include "linuxmemory.h"
#include "macmemory.h"
#include "linuxos.h"
#include "macos.h"
#include "linuxsoftware.h"
#include "macsoftware.h"
#include "linuxsystem.h"
#include "macsystem.h"

Info* Info::Factory(InfoType type)
{
    Architecture::OSType os = ARCH->osType();

    switch (type) {
        case Software:
            if (os == Architecture::Linux) {
                return new LinuxSoftware();
            } else if (os == Architecture::Darwin) {
                return new MacSoftware();
            }
            break;
        case Asset:
            if (os == Architecture::Linux) {
                return new LinuxAsset();
            } else if (os == Architecture::Darwin) {
                return new MacAsset();
            }
            break;
        case CPU:
            if (os == Architecture::Linux) {
                return new LinuxCPU();
            } else if (os == Architecture::Darwin) {
                return new MacCPU();
            }
            break;
        case Memory:
            if (os == Architecture::Linux) {
                return new LinuxMemory();
            } else if (os == Architecture::Darwin) {
                return new MacMemory();
            }
            break;
        case HardDrive:
            if (os == Architecture::Linux) {
                return new LinuxHardDrive();
            } else if (os == Architecture::Darwin) {
                return new MacHardDrive();
            }
            break;
        case System:
            if (os == Architecture::Linux) {
                return new LinuxSystem();
            } else if (os == Architecture::Darwin) {
                return new MacSystem();
            }
            break;
        case Network:
            if (os == Architecture::Linux) {
                return new LinuxNetwork();
            } else if (os == Architecture::Darwin) {
                return new MacNetwork();
            }
            break;
        default :
            // We don't know what to do, return null pointer
            return 0;
    }
    // We don't know what to do, return null pointer
    return 0;
}
