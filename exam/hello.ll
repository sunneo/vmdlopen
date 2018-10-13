; ModuleID = 'hello.c'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"Hello World\00", align 1
@.str1 = private unnamed_addr constant [2 x i8] c"1\00", align 1

; Function Attrs: nounwind
define void @hello() #0 {
  %1 = call i32 @puts(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0))
  ret void
}

declare i32 @puts(i8*) #1

; Function Attrs: nounwind
define i32 @one() #0 {
  %1 = call i32 @puts(i8* getelementptr inbounds ([2 x i8]* @.str1, i32 0, i32 0))
  ret i32 1
}

define i32 @main() #0{
   %ret = alloca i32 , align 4
   call void @hello()
   %1 = call i32 @one()
   store i32 %1, i32* %ret, align 4
   %2 = load i32* %ret, align 4
   ret i32 %2
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
