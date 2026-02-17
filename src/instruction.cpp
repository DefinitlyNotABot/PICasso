#include "instruction.hpp"

std::shared_ptr<MemoryInterface> Instruction::memoryInterface = nullptr;
std::shared_ptr<Register> Instruction::W = nullptr;
