; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/26.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = icmp ne i32 123, 0
  br i1 %2, label %label.trueBB, label %label.endBB
label.trueBB:
  store i32 1, i32* %1
  br label %label.endBB
label.endBB:
  %3 = load i32, i32* %1
  ret i32 %3
}
