# IAP-UPGRADE
The In-Application Programming ultilization using STM32F746NG Discovery Board.
The implementation requires the support of ST HAL library and the board support package(BSP
) of STM32F746NG
The IAP_BOOT programme needs to be downloaded in the very first stector of the flash. It receives the programmes that needs to upgrade by USART, then save them in some other sectors . After finishing receiving, it does the MD5 checking. If the checking goes right, the IAP_BOOT program then erase the sectors that holds the main programme and then move the saved programmes to the sectors. Finally it jumps to the start point of the new upgrade programme.
The IAP_Main give an example of the main programme that works regularly on board, the key source code is in the main() function. It receives the signal of upgrade and reset the PC to the IAP_BOOT programme.
