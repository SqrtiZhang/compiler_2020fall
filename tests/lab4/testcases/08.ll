; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/08.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define void @main() {
label.entry:
  call void @outputFloat(float 0x405ed999a0000000)
  ret void
}
