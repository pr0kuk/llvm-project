; ModuleID = 'logic.c'
source_filename = "logic.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Point = type { i32, i32, i32 }

@pixels = internal global [500 x [500 x %struct.Point]] zeroinitializer, align 16
@points = internal global [30 x %struct.Point] zeroinitializer, align 16
@flag_no_recalc = internal global i32 0, align 4
@pause_window = internal global i32 0, align 4
@show_window = internal global i32 1, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @dist(%struct.Point* %0, %struct.Point* %1) #0 {
  %3 = alloca %struct.Point*, align 8
  %4 = alloca %struct.Point*, align 8
  store %struct.Point* %0, %struct.Point** %3, align 8
  store %struct.Point* %1, %struct.Point** %4, align 8
  %5 = load %struct.Point*, %struct.Point** %4, align 8
  %6 = getelementptr inbounds %struct.Point, %struct.Point* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 4
  %8 = load %struct.Point*, %struct.Point** %3, align 8
  %9 = getelementptr inbounds %struct.Point, %struct.Point* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 4
  %11 = sub nsw i32 %7, %10
  %12 = load %struct.Point*, %struct.Point** %4, align 8
  %13 = getelementptr inbounds %struct.Point, %struct.Point* %12, i32 0, i32 1
  %14 = load i32, i32* %13, align 4
  %15 = load %struct.Point*, %struct.Point** %3, align 8
  %16 = getelementptr inbounds %struct.Point, %struct.Point* %15, i32 0, i32 1
  %17 = load i32, i32* %16, align 4
  %18 = sub nsw i32 %14, %17
  %19 = mul nsw i32 %11, %18
  %20 = load %struct.Point*, %struct.Point** %4, align 8
  %21 = getelementptr inbounds %struct.Point, %struct.Point* %20, i32 0, i32 2
  %22 = load i32, i32* %21, align 4
  %23 = load %struct.Point*, %struct.Point** %3, align 8
  %24 = getelementptr inbounds %struct.Point, %struct.Point* %23, i32 0, i32 2
  %25 = load i32, i32* %24, align 4
  %26 = sub nsw i32 %22, %25
  %27 = load %struct.Point*, %struct.Point** %4, align 8
  %28 = getelementptr inbounds %struct.Point, %struct.Point* %27, i32 0, i32 2
  %29 = load i32, i32* %28, align 4
  %30 = load %struct.Point*, %struct.Point** %3, align 8
  %31 = getelementptr inbounds %struct.Point, %struct.Point* %30, i32 0, i32 2
  %32 = load i32, i32* %31, align 4
  %33 = sub nsw i32 %29, %32
  %34 = mul nsw i32 %26, %33
  %35 = add nsw i32 %19, %34
  ret i32 %35
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @getrgb(i32 %0, float* %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca float*, align 8
  store i32 %0, i32* %3, align 4
  store float* %1, float** %4, align 8
  br label %5

5:                                                ; preds = %16, %2
  %6 = load i32, i32* %3, align 4
  %7 = icmp sgt i32 %6, 0
  br i1 %7, label %8, label %19

8:                                                ; preds = %5
  %9 = load float*, float** %4, align 8
  %10 = load i32, i32* %3, align 4
  %11 = srem i32 %10, 3
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds float, float* %9, i64 %12
  %14 = load float, float* %13, align 4
  %15 = fadd float %14, 0x3FB99999A0000000
  store float %15, float* %13, align 4
  br label %16

16:                                               ; preds = %8
  %17 = load i32, i32* %3, align 4
  %18 = sdiv i32 %17, 3
  store i32 %18, i32* %3, align 4
  br label %5

19:                                               ; preds = %5
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @calc_new_centers([500 x %struct.Point]* %0, %struct.Point* %1) #0 {
  %3 = alloca [500 x %struct.Point]*, align 8
  %4 = alloca %struct.Point*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca [30 x i32], align 16
  %8 = alloca [30 x i32], align 16
  %9 = alloca [30 x i32], align 16
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  store [500 x %struct.Point]* %0, [500 x %struct.Point]** %3, align 8
  store %struct.Point* %1, %struct.Point** %4, align 8
  store i32 0, i32* %5, align 4
  store i32 0, i32* %6, align 4
  store i32 0, i32* %10, align 4
  br label %14

14:                                               ; preds = %27, %2
  %15 = load i32, i32* %10, align 4
  %16 = icmp slt i32 %15, 30
  br i1 %16, label %17, label %30

17:                                               ; preds = %14
  %18 = load i32, i32* %10, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [30 x i32], [30 x i32]* %7, i64 0, i64 %19
  store i32 0, i32* %20, align 4
  %21 = load i32, i32* %10, align 4
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds [30 x i32], [30 x i32]* %8, i64 0, i64 %22
  store i32 0, i32* %23, align 4
  %24 = load i32, i32* %10, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [30 x i32], [30 x i32]* %9, i64 0, i64 %25
  store i32 0, i32* %26, align 4
  br label %27

27:                                               ; preds = %17
  %28 = load i32, i32* %10, align 4
  %29 = add nsw i32 %28, 1
  store i32 %29, i32* %10, align 4
  br label %14

30:                                               ; preds = %14
  store i32 0, i32* %11, align 4
  br label %31

31:                                               ; preds = %112, %30
  %32 = load i32, i32* %11, align 4
  %33 = icmp slt i32 %32, 500
  br i1 %33, label %34, label %115

34:                                               ; preds = %31
  store i32 0, i32* %12, align 4
  br label %35

35:                                               ; preds = %108, %34
  %36 = load i32, i32* %12, align 4
  %37 = icmp slt i32 %36, 500
  br i1 %37, label %38, label %111

38:                                               ; preds = %35
  %39 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %40 = load i32, i32* %11, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %39, i64 %41
  %43 = load i32, i32* %12, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %42, i64 0, i64 %44
  %46 = getelementptr inbounds %struct.Point, %struct.Point* %45, i32 0, i32 0
  %47 = load i32, i32* %46, align 4
  %48 = icmp sge i32 %47, 0
  br i1 %48, label %49, label %107

49:                                               ; preds = %38
  %50 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %51 = load i32, i32* %11, align 4
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %50, i64 %52
  %54 = load i32, i32* %12, align 4
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %53, i64 0, i64 %55
  %57 = getelementptr inbounds %struct.Point, %struct.Point* %56, i32 0, i32 1
  %58 = load i32, i32* %57, align 4
  %59 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %60 = load i32, i32* %11, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %59, i64 %61
  %63 = load i32, i32* %12, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %62, i64 0, i64 %64
  %66 = getelementptr inbounds %struct.Point, %struct.Point* %65, i32 0, i32 0
  %67 = load i32, i32* %66, align 4
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds [30 x i32], [30 x i32]* %7, i64 0, i64 %68
  %70 = load i32, i32* %69, align 4
  %71 = add nsw i32 %70, %58
  store i32 %71, i32* %69, align 4
  %72 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %73 = load i32, i32* %11, align 4
  %74 = sext i32 %73 to i64
  %75 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %72, i64 %74
  %76 = load i32, i32* %12, align 4
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %75, i64 0, i64 %77
  %79 = getelementptr inbounds %struct.Point, %struct.Point* %78, i32 0, i32 2
  %80 = load i32, i32* %79, align 4
  %81 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %82 = load i32, i32* %11, align 4
  %83 = sext i32 %82 to i64
  %84 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %81, i64 %83
  %85 = load i32, i32* %12, align 4
  %86 = sext i32 %85 to i64
  %87 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %84, i64 0, i64 %86
  %88 = getelementptr inbounds %struct.Point, %struct.Point* %87, i32 0, i32 0
  %89 = load i32, i32* %88, align 4
  %90 = sext i32 %89 to i64
  %91 = getelementptr inbounds [30 x i32], [30 x i32]* %8, i64 0, i64 %90
  %92 = load i32, i32* %91, align 4
  %93 = add nsw i32 %92, %80
  store i32 %93, i32* %91, align 4
  %94 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %95 = load i32, i32* %11, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %94, i64 %96
  %98 = load i32, i32* %12, align 4
  %99 = sext i32 %98 to i64
  %100 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %97, i64 0, i64 %99
  %101 = getelementptr inbounds %struct.Point, %struct.Point* %100, i32 0, i32 0
  %102 = load i32, i32* %101, align 4
  %103 = sext i32 %102 to i64
  %104 = getelementptr inbounds [30 x i32], [30 x i32]* %9, i64 0, i64 %103
  %105 = load i32, i32* %104, align 4
  %106 = add nsw i32 %105, 1
  store i32 %106, i32* %104, align 4
  br label %107

107:                                              ; preds = %49, %38
  br label %108

108:                                              ; preds = %107
  %109 = load i32, i32* %12, align 4
  %110 = add nsw i32 %109, 1
  store i32 %110, i32* %12, align 4
  br label %35

111:                                              ; preds = %35
  br label %112

112:                                              ; preds = %111
  %113 = load i32, i32* %11, align 4
  %114 = add nsw i32 %113, 1
  store i32 %114, i32* %11, align 4
  br label %31

115:                                              ; preds = %31
  store i32 0, i32* %13, align 4
  br label %116

116:                                              ; preds = %176, %115
  %117 = load i32, i32* %13, align 4
  %118 = icmp slt i32 %117, 30
  br i1 %118, label %119, label %179

119:                                              ; preds = %116
  %120 = load i32, i32* %13, align 4
  %121 = sext i32 %120 to i64
  %122 = getelementptr inbounds [30 x i32], [30 x i32]* %7, i64 0, i64 %121
  %123 = load i32, i32* %122, align 4
  %124 = load i32, i32* %13, align 4
  %125 = sext i32 %124 to i64
  %126 = getelementptr inbounds [30 x i32], [30 x i32]* %9, i64 0, i64 %125
  %127 = load i32, i32* %126, align 4
  %128 = sdiv i32 %123, %127
  store i32 %128, i32* %6, align 4
  %129 = load %struct.Point*, %struct.Point** %4, align 8
  %130 = load i32, i32* %13, align 4
  %131 = sext i32 %130 to i64
  %132 = getelementptr inbounds %struct.Point, %struct.Point* %129, i64 %131
  %133 = getelementptr inbounds %struct.Point, %struct.Point* %132, i32 0, i32 1
  %134 = load i32, i32* %133, align 4
  %135 = load i32, i32* %6, align 4
  %136 = icmp eq i32 %134, %135
  br i1 %136, label %137, label %140

137:                                              ; preds = %119
  %138 = load i32, i32* %5, align 4
  %139 = add nsw i32 %138, 1
  store i32 %139, i32* %5, align 4
  br label %147

140:                                              ; preds = %119
  %141 = load i32, i32* %6, align 4
  %142 = load %struct.Point*, %struct.Point** %4, align 8
  %143 = load i32, i32* %13, align 4
  %144 = sext i32 %143 to i64
  %145 = getelementptr inbounds %struct.Point, %struct.Point* %142, i64 %144
  %146 = getelementptr inbounds %struct.Point, %struct.Point* %145, i32 0, i32 1
  store i32 %141, i32* %146, align 4
  br label %147

147:                                              ; preds = %140, %137
  %148 = load i32, i32* %13, align 4
  %149 = sext i32 %148 to i64
  %150 = getelementptr inbounds [30 x i32], [30 x i32]* %8, i64 0, i64 %149
  %151 = load i32, i32* %150, align 4
  %152 = load i32, i32* %13, align 4
  %153 = sext i32 %152 to i64
  %154 = getelementptr inbounds [30 x i32], [30 x i32]* %9, i64 0, i64 %153
  %155 = load i32, i32* %154, align 4
  %156 = sdiv i32 %151, %155
  store i32 %156, i32* %6, align 4
  %157 = load %struct.Point*, %struct.Point** %4, align 8
  %158 = load i32, i32* %13, align 4
  %159 = sext i32 %158 to i64
  %160 = getelementptr inbounds %struct.Point, %struct.Point* %157, i64 %159
  %161 = getelementptr inbounds %struct.Point, %struct.Point* %160, i32 0, i32 2
  %162 = load i32, i32* %161, align 4
  %163 = load i32, i32* %6, align 4
  %164 = icmp eq i32 %162, %163
  br i1 %164, label %165, label %168

165:                                              ; preds = %147
  %166 = load i32, i32* %5, align 4
  %167 = add nsw i32 %166, 1
  store i32 %167, i32* %5, align 4
  br label %175

168:                                              ; preds = %147
  %169 = load i32, i32* %6, align 4
  %170 = load %struct.Point*, %struct.Point** %4, align 8
  %171 = load i32, i32* %13, align 4
  %172 = sext i32 %171 to i64
  %173 = getelementptr inbounds %struct.Point, %struct.Point* %170, i64 %172
  %174 = getelementptr inbounds %struct.Point, %struct.Point* %173, i32 0, i32 2
  store i32 %169, i32* %174, align 4
  br label %175

175:                                              ; preds = %168, %165
  br label %176

176:                                              ; preds = %175
  %177 = load i32, i32* %13, align 4
  %178 = add nsw i32 %177, 1
  store i32 %178, i32* %13, align 4
  br label %116

179:                                              ; preds = %116
  %180 = load i32, i32* %5, align 4
  ret i32 %180
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @calc_vor_diag([500 x %struct.Point]* %0, %struct.Point* %1) #0 {
  %3 = alloca [500 x %struct.Point]*, align 8
  %4 = alloca %struct.Point*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store [500 x %struct.Point]* %0, [500 x %struct.Point]** %3, align 8
  store %struct.Point* %1, %struct.Point** %4, align 8
  store i32 0, i32* %5, align 4
  br label %10

10:                                               ; preds = %79, %2
  %11 = load i32, i32* %5, align 4
  %12 = icmp slt i32 %11, 500
  br i1 %12, label %13, label %82

13:                                               ; preds = %10
  store i32 0, i32* %6, align 4
  store i32 1000000000, i32* %7, align 4
  br label %14

14:                                               ; preds = %57, %13
  %15 = load i32, i32* %6, align 4
  %16 = icmp slt i32 %15, 500
  br i1 %16, label %17, label %78

17:                                               ; preds = %14
  store i32 0, i32* %8, align 4
  store i32 0, i32* %9, align 4
  br label %18

18:                                               ; preds = %53, %17
  %19 = load i32, i32* %8, align 4
  %20 = icmp slt i32 %19, 30
  br i1 %20, label %21, label %24

21:                                               ; preds = %18
  %22 = load i32, i32* %7, align 4
  %23 = icmp sgt i32 %22, 0
  br label %24

24:                                               ; preds = %21, %18
  %25 = phi i1 [ false, %18 ], [ %23, %21 ]
  br i1 %25, label %26, label %56

26:                                               ; preds = %24
  %27 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %28 = load i32, i32* %5, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %27, i64 %29
  %31 = load i32, i32* %6, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %30, i64 0, i64 %32
  %34 = load %struct.Point*, %struct.Point** %4, align 8
  %35 = load i32, i32* %8, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds %struct.Point, %struct.Point* %34, i64 %36
  %38 = call i32 @dist(%struct.Point* %33, %struct.Point* %37)
  store i32 %38, i32* %9, align 4
  %39 = load i32, i32* %7, align 4
  %40 = icmp slt i32 %38, %39
  br i1 %40, label %41, label %52

41:                                               ; preds = %26
  %42 = load i32, i32* %9, align 4
  store i32 %42, i32* %7, align 4
  %43 = load i32, i32* %8, align 4
  %44 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %45 = load i32, i32* %5, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %44, i64 %46
  %48 = load i32, i32* %6, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %47, i64 0, i64 %49
  %51 = getelementptr inbounds %struct.Point, %struct.Point* %50, i32 0, i32 0
  store i32 %43, i32* %51, align 4
  br label %52

52:                                               ; preds = %41, %26
  br label %53

53:                                               ; preds = %52
  %54 = load i32, i32* %8, align 4
  %55 = add nsw i32 %54, 1
  store i32 %55, i32* %8, align 4
  br label %18

56:                                               ; preds = %24
  br label %57

57:                                               ; preds = %56
  %58 = load i32, i32* %6, align 4
  %59 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %60 = load i32, i32* %5, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %59, i64 %61
  %63 = load i32, i32* %6, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %62, i64 0, i64 %64
  %66 = getelementptr inbounds %struct.Point, %struct.Point* %65, i32 0, i32 1
  store i32 %58, i32* %66, align 4
  %67 = load i32, i32* %5, align 4
  %68 = load [500 x %struct.Point]*, [500 x %struct.Point]** %3, align 8
  %69 = load i32, i32* %5, align 4
  %70 = sext i32 %69 to i64
  %71 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %68, i64 %70
  %72 = load i32, i32* %6, align 4
  %73 = sext i32 %72 to i64
  %74 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %71, i64 0, i64 %73
  %75 = getelementptr inbounds %struct.Point, %struct.Point* %74, i32 0, i32 2
  store i32 %67, i32* %75, align 4
  %76 = load i32, i32* %6, align 4
  %77 = add nsw i32 %76, 1
  store i32 %77, i32* %6, align 4
  store i32 1000000000, i32* %7, align 4
  br label %14

78:                                               ; preds = %14
  br label %79

79:                                               ; preds = %78
  %80 = load i32, i32* %5, align 4
  %81 = add nsw i32 %80, 1
  store i32 %81, i32* %5, align 4
  br label %10

82:                                               ; preds = %10
  ret i32 0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @display() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = call i32 @calc_vor_diag([500 x %struct.Point]* getelementptr inbounds ([500 x [500 x %struct.Point]], [500 x [500 x %struct.Point]]* @pixels, i64 0, i64 0), %struct.Point* getelementptr inbounds ([30 x %struct.Point], [30 x %struct.Point]* @points, i64 0, i64 0))
  call void (...) @gl_start()
  store i32 0, i32* %1, align 4
  br label %4

4:                                                ; preds = %22, %0
  %5 = load i32, i32* %1, align 4
  %6 = icmp slt i32 %5, 500
  br i1 %6, label %7, label %25

7:                                                ; preds = %4
  store i32 0, i32* %2, align 4
  br label %8

8:                                                ; preds = %18, %7
  %9 = load i32, i32* %2, align 4
  %10 = icmp slt i32 %9, 500
  br i1 %10, label %11, label %21

11:                                               ; preds = %8
  %12 = load i32, i32* %1, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [500 x [500 x %struct.Point]], [500 x [500 x %struct.Point]]* @pixels, i64 0, i64 %13
  %15 = load i32, i32* %2, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [500 x %struct.Point], [500 x %struct.Point]* %14, i64 0, i64 %16
  call void @gl_put_pixel(%struct.Point* %17)
  br label %18

18:                                               ; preds = %11
  %19 = load i32, i32* %2, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, i32* %2, align 4
  br label %8

21:                                               ; preds = %8
  br label %22

22:                                               ; preds = %21
  %23 = load i32, i32* %1, align 4
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %1, align 4
  br label %4

25:                                               ; preds = %4
  call void (...) @gl_flush()
  ret void
}

declare dso_local void @gl_start(...) #1

declare dso_local void @gl_put_pixel(%struct.Point*) #1

declare dso_local void @gl_flush(...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @timf(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* @flag_no_recalc, align 4
  %4 = icmp eq i32 %3, 0
  br i1 %4, label %5, label %14

5:                                                ; preds = %1
  %6 = load i32, i32* @pause_window, align 4
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %8, label %14

8:                                                ; preds = %5
  %9 = call i32 @calc_new_centers([500 x %struct.Point]* getelementptr inbounds ([500 x [500 x %struct.Point]], [500 x [500 x %struct.Point]]* @pixels, i64 0, i64 0), %struct.Point* getelementptr inbounds ([30 x %struct.Point], [30 x %struct.Point]* @points, i64 0, i64 0))
  %10 = icmp slt i32 %9, 60
  br i1 %10, label %11, label %12

11:                                               ; preds = %8
  call void @display()
  br label %13

12:                                               ; preds = %8
  store i32 1, i32* @flag_no_recalc, align 4
  br label %13

13:                                               ; preds = %12, %11
  br label %14

14:                                               ; preds = %13, %5, %1
  %15 = load i32, i32* %2, align 4
  call void @set_timer(i32 %15)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @set_timer(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @reset_picture() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  br label %2

2:                                                ; preds = %18, %0
  %3 = load i32, i32* %1, align 4
  %4 = icmp slt i32 %3, 30
  br i1 %4, label %5, label %21

5:                                                ; preds = %2
  %6 = call i32 @rand() #3
  %7 = srem i32 %6, 500
  %8 = load i32, i32* %1, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [30 x %struct.Point], [30 x %struct.Point]* @points, i64 0, i64 %9
  %11 = getelementptr inbounds %struct.Point, %struct.Point* %10, i32 0, i32 1
  store i32 %7, i32* %11, align 4
  %12 = call i32 @rand() #3
  %13 = srem i32 %12, 500
  %14 = load i32, i32* %1, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [30 x %struct.Point], [30 x %struct.Point]* @points, i64 0, i64 %15
  %17 = getelementptr inbounds %struct.Point, %struct.Point* %16, i32 0, i32 2
  store i32 %13, i32* %17, align 4
  br label %18

18:                                               ; preds = %5
  %19 = load i32, i32* %1, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, i32* %1, align 4
  br label %2

21:                                               ; preds = %2
  %22 = call i32 @calc_vor_diag([500 x %struct.Point]* getelementptr inbounds ([500 x [500 x %struct.Point]], [500 x [500 x %struct.Point]]* @pixels, i64 0, i64 0), %struct.Point* getelementptr inbounds ([30 x %struct.Point], [30 x %struct.Point]* @points, i64 0, i64 0))
  store i32 0, i32* @flag_no_recalc, align 4
  ret void
}

; Function Attrs: nounwind
declare dso_local i32 @rand() #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @releaseKey(i8 zeroext %0, i32 %1, i32 %2) #0 {
  %4 = alloca i8, align 1
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i8 %0, i8* %4, align 1
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %7 = load i8, i8* %4, align 1
  %8 = zext i8 %7 to i32
  switch i32 %8, label %14 [
    i32 27, label %9
    i32 32, label %10
    i32 114, label %13
  ]

9:                                                ; preds = %3
  call void @exit_loop()
  br label %14

10:                                               ; preds = %3
  %11 = load i32, i32* @pause_window, align 4
  %12 = xor i32 %11, 1
  store i32 %12, i32* @pause_window, align 4
  br label %14

13:                                               ; preds = %3
  call void @reset_picture()
  br label %14

14:                                               ; preds = %3, %13, %10, %9
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @loop() #0 {
  call void @display()
  br label %1

1:                                                ; preds = %4, %0
  %2 = load i32, i32* @show_window, align 4
  %3 = icmp eq i32 %2, 1
  br i1 %3, label %4, label %5

4:                                                ; preds = %1
  call void @timf(i32 40)
  br label %1

5:                                                ; preds = %1
  ret i32 0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @exit_loop() #0 {
  store i32 0, i32* @show_window, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %6 = load i32, i32* %4, align 4
  %7 = load i8**, i8*** %5, align 8
  %8 = call i32 @gl_init(i32 %6, i8** %7)
  call void @reset_picture()
  %9 = call i32 @loop()
  ret i32 0
}

declare dso_local i32 @gl_init(i32, i8**) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
