; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/11.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define void @main() {
label.entry:
  %0 = alloca i32
  store float 0x3ff0000000000000, i32* %0
  call void @output(i32* %0)
  ret void
}
