; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/17.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = fptosi float 0x4017333340000000 to i32
  ret i32 %1
}
