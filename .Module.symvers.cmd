cmd_/home/gabriel/Trab-SO/Module.symvers := sed 's/\.ko$$/\.o/' /home/gabriel/Trab-SO/modules.order | scripts/mod/modpost -m -a  -o /home/gabriel/Trab-SO/Module.symvers -e -i Module.symvers   -T -
