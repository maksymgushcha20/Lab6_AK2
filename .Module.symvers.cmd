cmd_/home/ubuntu20/SP_lab_work/Lab6/Module.symvers := sed 's/\.ko$$/\.o/' /home/ubuntu20/SP_lab_work/Lab6/modules.order | scripts/mod/modpost -m -a  -o /home/ubuntu20/SP_lab_work/Lab6/Module.symvers -e -i Module.symvers   -T -
