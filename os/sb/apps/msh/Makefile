##############################################################################
# Multi-project makefile rules
#

all:
	@echo
	@echo === Building for MSH-RAMBOX-DEPLOY =================================
	+@make --no-print-directory -f ./make/msh-rambox-deploy.make all
	@echo ====================================================================
	@echo
	@echo === Building for MSH-RAMBOX-DEBUG ==================================
	+@make --no-print-directory -f ./make/msh-rambox-debug.make all
	@echo ====================================================================
	@echo
	@echo === Building for MSH-32k-081F0000-128k-20060000 ====================
	+@make --no-print-directory -f ./make/msh-32k-081F0000-128k-20060000.make all
	@echo ====================================================================
	@echo
	@echo === Building for MSH-32k-081F8000-128k-20080000 ====================
	+@make --no-print-directory -f ./make/msh-32k-081F8000-128k-20080000.make all
	@echo ====================================================================
	@echo

clean:
	@echo
	+@make --no-print-directory -f ./make/msh-rambox-deploy.make clean
	@echo
	+@make --no-print-directory -f ./make/msh-rambox-debug.make clean
	@echo
	+@make --no-print-directory -f ./make/msh-32k-081F0000-128k-20060000.make clean
	@echo
	+@make --no-print-directory -f ./make/msh-32k-081F8000-128k-20080000.make clean
	@echo

#
##############################################################################
