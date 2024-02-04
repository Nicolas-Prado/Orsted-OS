from PageEntity import PageEntity

brokenhorn = PageEntity('http://www.brokenthorn.com/Resources/', 'brokenhorn')

#brokenhorn.extractPage('HomePage', 'OSDevIndex.html')

#Bootloaders
brokenhorn.extractPage('1_Preface', 'OSDev0.html')
brokenhorn.extractPage('2_Introduction', 'OSDev1.html')
brokenhorn.extractPage('3_Theory', 'OSDev2.html')
brokenhorn.extractPage('4_Bootloaders1', 'OSDev3.html')
brokenhorn.extractPage('5_Bootloaders2', 'OSDev4.html')
brokenhorn.extractPage('6_Bootloaders3', 'OSDev5.html')
brokenhorn.extractPage('7_Bootloaders4', 'OSDev6.html')

#Stage 2
brokenhorn.extractPage('1_SystemArchitecture', 'OSDev7.html')
brokenhorn.extractPage('2_ProtectedMode', 'OSDev8.html')
brokenhorn.extractPage('3_A20', 'OSDev9.html')
brokenhorn.extractPage('4_PrepareKernel1', 'OSDev10.html')
brokenhorn.extractPage('5_PrepareKernel2', 'OSDev11.html')

#The Kernel: Setting up
brokenhorn.extractPage('1_KernelBasic', 'OSDev12.html')
brokenhorn.extractPage('2_KernelBasic', 'OSDev13.html')
brokenhorn.extractPage('3_MSVC', 'OSDevMSVC.html')

#The Kernel
brokenhorn.extractPage('1_KernelCRT', 'OSDev14.html')
brokenhorn.extractPage('2_KernelInt', 'OSDev15.html')
brokenhorn.extractPage('3_KernelPIC', 'OSDev16.html')
brokenhorn.extractPage('4_KernelPhysicalMemory', 'OSDev17.html')
brokenhorn.extractPage('5_KernelVirtualMemory', 'OSDev18.html')
brokenhorn.extractPage('6_Keyboard', 'OSDev19.html')
brokenhorn.extractPage('7_FDCProgramming', 'OSDev20.html')
brokenhorn.extractPage('8_DMAProgramming', 'OSDev21.html')
brokenhorn.extractPage('9_FileSystems', 'OSDev22.html')
brokenhorn.extractPage('10_UserLand', 'OSDev23.html')
brokenhorn.extractPage('11_ProcessManagement1', 'OSDev24.html')
brokenhorn.extractPage('12_ProcessManagement2', 'OSDev25.html')

#File formats
brokenhorn.extractPage('1_PortableExecutable', 'OSDevPE.html')

#Microcontrollers
brokenhorn.extractPage('PIC', 'OSDevPic.html')
brokenhorn.extractPage('PIT', 'OSDevPit.html')

#Graphics
brokenhorn.extractPage('1_Graphics', 'OSDevVga.html')
brokenhorn.extractPage('2_Graphics', 'OSDevVid2.html')

#Standards
brokenhorn.extractPage('Multiboot', 'OSDevMulti.html')
brokenhorn.extractPage('ScanCodes', 'OSDevScanCodes.html')
brokenhorn.extractPage('IA32_IA64', 'OSDevX86.html')