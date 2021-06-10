; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/19.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca float
  %2 = alloca i32
  store float 0x401f9999a0000000, float* %1
  store i32 5, i32* %2
  %3 = load float, float* %1
  %4 = load i32, i32* %2
  %5 = sitofp i32 %4 to float
  %6 = fcmp ult float %3,%5
  br i1 %6, label %label.trueBB, label %label.retBB
label.trueBB:
  ret i32 1
label.retBB:
  ret i32 3
}
