cmd_/home/gabriel/Trab-SO/modules.order := {   echo /home/gabriel/Trab-SO/mymodule.ko; :; } | awk '!x[$$0]++' - > /home/gabriel/Trab-SO/modules.order
