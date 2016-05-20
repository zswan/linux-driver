(1)0001-optimize-rpmb-driver-access-inteface-for-PSP.patch
	This patch is relative to "0001-add-eMMC-rpmb-driver-access-interface-in-Kernel-side.patch".
	If you have already merged this "0001-add-eMMC-rpmb-driver-access-interface-in-Kernel-side.patch",
	you only need merge the "0001-optimize-rpmb-driver-access-inteface-for-PSP.patch".
	
	if you encountered some issues duration on merging the patch, please see "emmc driver" folder.
	I copy my block.c directly to you, and there is a little modification, and you can compare it
	with your previous one to see what I have modified.
	
(2)emmc driver folder
	As my comments above, in case you can not merge my optimize patch normally, you can add it by your hands.

(3)rpmb_test_driver.c
	This driver is test app for new, optimized rpmb access driver.
	you can make reference to it, and modify it per your situation.