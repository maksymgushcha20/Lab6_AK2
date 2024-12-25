cmd_/home/ubuntu20/SP_lab_work/Lab6/modules.order := {   echo /home/ubuntu20/SP_lab_work/Lab6/hello.ko; :; } | awk '!x[$$0]++' - > /home/ubuntu20/SP_lab_work/Lab6/modules.order
