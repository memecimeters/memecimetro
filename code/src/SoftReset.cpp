
void softReset() { // Restarts program from beginning but does not reset the peripherals and registers
  asm volatile ("  jmp 0");
}
