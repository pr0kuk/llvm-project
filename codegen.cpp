#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include <iostream>
#include <string>
#include <unordered_map>
void reset_picture();
void gl_init(int argc, char** argv);
void loop();
llvm::ArrayType* pixels_subtype;
llvm::StructType* Point;
llvm::ArrayType* pixels_type;

void LLVM_main() {
    std::cout << "ALIVE!!" << std::endl;
    // gl_init(argc, argv);
    // reset_picture();
    // loop();
}

void dump_codegen(llvm::Module* module) {
    std::string s;
    llvm::raw_string_ostream os(s);
    module->print(os, nullptr);
    os.flush();
    std::cout << s;
}

void reset_picture_codegen(llvm::Module* module, llvm::IRBuilder<>* builder)  {
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& reset_pictureFunc = module->getFunction("reset_picture");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", reset_pictureFunc);
    builder->SetInsertPoint(entry);

    id2bb[2] = llvm::BasicBlock::Create(module->getContext(), "2", reset_pictureFunc );
    id2bb[5] = llvm::BasicBlock::Create(module->getContext(), "5", reset_pictureFunc );
    id2bb[18] = llvm::BasicBlock::Create(module->getContext(), "18", reset_pictureFunc );
    id2bb[21] = llvm::BasicBlock::Create(module->getContext(), "21", reset_pictureFunc );


//   %1 = alloca i32, align 4
//   store i32 0, i32* %1, align 4
//   br label %2
    id2value[1] = builder->CreateAlloca(builder->getInt32Ty());
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[1]);
    builder->CreateBr(id2bb[2]);
    std::cout << "aft reset 1block" << std::endl;

// 2:                                                ; preds = %18, %0
//   %3 = load i32, i32* %1, align 4
//   %4 = icmp slt i32 %3, 10
//   br i1 %4, label %5, label %21
    builder->SetInsertPoint(id2bb[2]);
    id2value[3] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[4] = builder->CreateICmpSLT(id2value[3], llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    builder->CreateCondBr(id2value[4], id2bb[5], id2bb[21]);
    std::cout << "aft reset 2 block" << std::endl;


// 5:                                                ; preds = %2
//   %6 = call i32 (...) @int_rand()
//   %7 = srem i32 %6, 800
//   %8 = load i32, i32* %1, align 4
//   %9 = sext i32 %8 to i64
//   %10 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %9
//   %11 = getelementptr inbounds %struct.Point, %struct.Point* %10, i32 0, i32 1
//   store i32 %7, i32* %11, align 4
//   %12 = call i32 (...) @int_rand()
//   %13 = srem i32 %12, 800
//   %14 = load i32, i32* %1, align 4
//   %15 = sext i32 %14 to i64
//   %16 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %15
//   %17 = getelementptr inbounds %struct.Point, %struct.Point* %16, i32 0, i32 2
//   store i32 %13, i32* %17, align 4
//   br label %18

    builder->SetInsertPoint(id2bb[5]);
    auto int_randFunc = module->getFunction("int_rand");
    id2value[6] = builder->CreateCall(int_randFunc);
    std::cout << "aft reset rand" << std::endl;
    id2value[7] = builder->CreateSRem(id2value[6], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    id2value[8] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[9] = builder->CreateSExt(id2value[8], builder->getInt64Ty());
    std::cout << "bef reset 1 gep" << std::endl;
    auto&& points = module->getNamedGlobal ("points");
    id2value[10] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[9]});
    id2value[11] = builder->CreateInBoundsGEP(Point, id2value[10], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)});
    builder->CreateStore(id2value[7], id2value[11]);
    id2value[12] = builder->CreateCall(int_randFunc);
    id2value[13] = builder->CreateSRem(id2value[12], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    id2value[14] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[15] = builder->CreateSExt(id2value[14], builder->getInt64Ty());
    id2value[16] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[15]});
    id2value[17] = builder->CreateInBoundsGEP(Point, id2value[16], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)});
    builder->CreateStore(id2value[13], id2value[17]);
    builder->CreateBr(id2bb[18]);

// 18:                                               ; preds = %5
//   %19 = load i32, i32* %1, align 4
//   %20 = add nsw i32 %19, 1
//   store i32 %20, i32* %1, align 4
//   br label %2

    builder->SetInsertPoint(id2bb[18]);
    id2value[19] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[20] = builder->CreateNSWAdd(id2value[19], llvm::ConstantInt::get(builder->getInt32Ty(), 1));
    builder->CreateStore(id2value[20], id2value[1]);
    builder->CreateBr(id2bb[2]);


// 21:                                               ; preds = %2
//   call void @calc_vor_diag([800 x %struct.Point]* getelementptr inbounds ([800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 0), %struct.Point* getelementptr inbounds ([10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 0))
//   store i32 0, i32* @flag_no_recalc, align 4
//   ret void

    builder->SetInsertPoint(id2bb[21]);
    auto calc_vor_diagFunc = module->getFunction("calc_vor_diag");
    builder->CreateCall(calc_vor_diagFunc);
    auto flag_no_recalc = module->getNamedGlobal("flag_no_recalc");
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 1), flag_no_recalc);
    builder->CreateRetVoid();
}

void dist_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;
    llvm::StructType* Point = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());
    auto PPoint = llvm::PointerType::get(Point, 0);
    auto&& distFunc = module->getFunction("dist");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", distFunc);
    builder->SetInsertPoint(entry);
    id2value[0] = distFunc->getArg(0);
    id2value[1] = distFunc->getArg(1);
//   %3 = alloca %struct.Point*, align 8
//   %4 = alloca %struct.Point*, align 8
//   store %struct.Point* %0, %struct.Point** %3, align 8
//   store %struct.Point* %1, %struct.Point** %4, align 8
//   %5 = load %struct.Point*, %struct.Point** %4, align 8
//   %6 = getelementptr inbounds %struct.Point, %struct.Point* %5, i32 0, i32 1
//   %7 = load i32, i32* %6, align 4
//   %8 = load %struct.Point*, %struct.Point** %3, align 8
//   %9 = getelementptr inbounds %struct.Point, %struct.Point* %8, i32 0, i32 1
//   %10 = load i32, i32* %9, align 4
//   %11 = sub nsw i32 %7, %10
//   %12 = load %struct.Point*, %struct.Point** %4, align 8
//   %13 = getelementptr inbounds %struct.Point, %struct.Point* %12, i32 0, i32 1
//   %14 = load i32, i32* %13, align 4
//   %15 = load %struct.Point*, %struct.Point** %3, align 8
//   %16 = getelementptr inbounds %struct.Point, %struct.Point* %15, i32 0, i32 1
//llvm::StructType* PPoint = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());

    //auto PPoint = 
    id2value[3] = builder->CreateAlloca(PPoint);
    id2value[4] = builder->CreateAlloca(PPoint);

    builder->CreateStore(id2value[0], id2value[3]);
    builder->CreateStore(id2value[1], id2value[4]);
    id2value[5] = builder->CreateLoad(PPoint, id2value[4]);
    id2value[6] = builder->CreateInBoundsGEP(Point, id2value[5], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[8] = builder->CreateLoad(PPoint, id2value[3]);
    id2value[9] = builder->CreateInBoundsGEP(Point, id2value[8], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );
    id2value[10] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[11] = builder->CreateNSWSub(id2value[7], id2value[10]);
    id2value[12] = builder->CreateLoad(PPoint, id2value[4]);
    id2value[13] = builder->CreateInBoundsGEP(Point, id2value[12], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );
    id2value[14] = builder->CreateLoad(builder->getInt32Ty(), id2value[13]);
    id2value[15] = builder->CreateLoad(PPoint, id2value[3]);
    id2value[16] = builder->CreateInBoundsGEP(Point, id2value[15], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );


//   %17 = load i32, i32* %16, align 4
//   %18 = sub nsw i32 %14, %17
//   %19 = mul nsw i32 %11, %18
//   %20 = load %struct.Point*, %struct.Point** %4, align 8
//   %21 = getelementptr inbounds %struct.Point, %struct.Point* %20, i32 0, i32 2
//   %22 = load i32, i32* %21, align 4
//   %23 = load %struct.Point*, %struct.Point** %3, align 8
//   %24 = getelementptr inbounds %struct.Point, %struct.Point* %23, i32 0, i32 2
//   %25 = load i32, i32* %24, align 4
//   %26 = sub nsw i32 %22, %25
//   %27 = load %struct.Point*, %struct.Point** %4, align 8
//   %28 = getelementptr inbounds %struct.Point, %struct.Point* %27, i32 0, i32 2
//   %29 = load i32, i32* %28, align 4
//   %30 = load %struct.Point*, %struct.Point** %3, align 8
//   %31 = getelementptr inbounds %struct.Point, %struct.Point* %30, i32 0, i32 2
//   %32 = load i32, i32* %31, align 4
//   %33 = sub nsw i32 %29, %32
//   %34 = mul nsw i32 %26, %33
//   %35 = add nsw i32 %19, %34
//   ret i32 %35
    id2value[17] = builder->CreateLoad(builder->getInt32Ty(), id2value[16]);
    id2value[18] = builder->CreateNSWSub(id2value[14], id2value[17]);
    id2value[19] = builder->CreateNSWMul(id2value[11], id2value[18]);
    id2value[20] = builder->CreateLoad(PPoint, id2value[4]);
    id2value[21] = builder->CreateInBoundsGEP(Point, id2value[20], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[21]);
    id2value[23] = builder->CreateLoad(PPoint, id2value[3]);
    id2value[24] = builder->CreateInBoundsGEP(Point, id2value[23], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[25] = builder->CreateLoad(builder->getInt32Ty(), id2value[24]);
    id2value[26] = builder->CreateNSWSub(id2value[22], id2value[25]);
    id2value[27] = builder->CreateLoad(PPoint, id2value[4]);
    id2value[28] = builder->CreateInBoundsGEP(Point, id2value[27], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[29] = builder->CreateLoad(builder->getInt32Ty(), id2value[28]);
    id2value[30] = builder->CreateLoad(PPoint, id2value[3]);
    id2value[31] = builder->CreateInBoundsGEP(Point, id2value[30], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[32] = builder->CreateLoad(builder->getInt32Ty(), id2value[31]);
    id2value[33] = builder->CreateNSWSub(id2value[29], id2value[32]);
    id2value[34] = builder->CreateNSWMul(id2value[26], id2value[33]);
    id2value[35] = builder->CreateNSWAdd(id2value[19], id2value[34]);
    builder->CreateRet(id2value[35]);
}

void display_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;
    auto&& displayFunc = module->getFunction("display");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", displayFunc);
    builder->SetInsertPoint(entry);
    id2bb[3] = llvm::BasicBlock::Create(module->getContext(), "3", displayFunc );
    id2bb[6] = llvm::BasicBlock::Create(module->getContext(), "6", displayFunc );
    id2bb[7] = llvm::BasicBlock::Create(module->getContext(), "7", displayFunc );
    id2bb[10] = llvm::BasicBlock::Create(module->getContext(), "10", displayFunc );
    id2bb[17] = llvm::BasicBlock::Create(module->getContext(), "17", displayFunc );
    id2bb[20] = llvm::BasicBlock::Create(module->getContext(), "20", displayFunc );
    id2bb[21] = llvm::BasicBlock::Create(module->getContext(), "21", displayFunc );
    id2bb[24] = llvm::BasicBlock::Create(module->getContext(), "24", displayFunc );


//   %1 = alloca i32, align 4
//   %2 = alloca i32, align 4
//   call void @calc_vor_diag()
//   call void (...) @gl_start()
//   store i32 0, i32* %1, align 4
//   br label %3
    id2value[1] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[2] = builder->CreateAlloca(builder->getInt32Ty());
    auto calc_vor_diagFunc = module->getFunction("calc_vor_diag");
    builder->CreateCall(calc_vor_diagFunc);
    auto gl_startFunc = module->getFunction("gl_start");
    builder->CreateCall(gl_startFunc);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[1]);
    builder->CreateBr(id2bb[3]);

// 3:                                                ; preds = %21, %0
//   %4 = load i32, i32* %1, align 4
//   %5 = icmp slt i32 %4, 800
//   br i1 %5, label %6, label %24

    builder->SetInsertPoint(id2bb[3]);
    id2value[4] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[5] = builder->CreateICmpSLT(id2value[4], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateCondBr(id2value[5], id2bb[6], id2bb[24]);

// 6:                                                ; preds = %3
//   store i32 0, i32* %2, align 4
//   br label %7

    builder->SetInsertPoint(id2bb[6]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[2]);
    builder->CreateBr(id2bb[7]);


// 7:                                                ; preds = %17, %6
//   %8 = load i32, i32* %2, align 4
//   %9 = icmp slt i32 %8, 800
//   br i1 %9, label %10, label %20


    builder->SetInsertPoint(id2bb[7]);
    id2value[8] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[9] = builder->CreateICmpSLT(id2value[8], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateCondBr(id2value[11], id2bb[10], id2bb[20]);
// 10:                                               ; preds = %7
//   %11 = load i32, i32* %1, align 4
//   %12 = sext i32 %11 to i64
//   %13 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %12
//   %14 = load i32, i32* %2, align 4
//   %15 = sext i32 %14 to i64
//   %16 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %13, i64 0, i64 %15
//   call void @gl_put_pixel(%struct.Point* %16)
//   br label %17

    builder->SetInsertPoint(id2bb[10]);
    id2value[11] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[12] = builder->CreateSExt(id2value[11], builder->getInt64Ty());
    auto&& pixels = module->getNamedGlobal ("pixels");
    auto&& points = module->getNamedGlobal ("points");

    id2value[13] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[12]});
    id2value[14] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[15] = builder->CreateSExt(id2value[14], builder->getInt64Ty());
    id2value[16] = builder->CreateInBoundsGEP(pixels_subtype, id2value[13], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[15]});
    auto gl_put_pixelFunc = module->getFunction("gl_put_pixel");
    builder->CreateCall(gl_put_pixelFunc, id2value[16]);
    builder->CreateBr(id2bb[17]);

// 17:                                               ; preds = %10
//   %18 = load i32, i32* %2, align 4
//   %19 = add nsw i32 %18, 1
//   store i32 %19, i32* %2, align 4
//   br label %7


    builder->SetInsertPoint(id2bb[17]);
    id2value[18] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[19] = builder->CreateNSWAdd(id2value[18],llvm::ConstantInt::get(builder->getInt64Ty(), 1) );
    builder->CreateStore(id2value[19], id2value[2]);
    builder->CreateBr(id2bb[7]);

// 20:                                               ; preds = %7
//   br label %21
    builder->SetInsertPoint(id2bb[20]);
    builder->CreateBr(id2bb[21]);
// 21:                                               ; preds = %20
//   %22 = load i32, i32* %1, align 4
//   %23 = add nsw i32 %22, 1
//   store i32 %23, i32* %1, align 4
//   br label %3
    builder->SetInsertPoint(id2bb[21]);
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[23] = builder->CreateNSWAdd(id2value[18],llvm::ConstantInt::get(builder->getInt64Ty(), 1) );
    builder->CreateStore(id2value[23], id2value[1]);
    builder->CreateBr(id2bb[3]);
// 24:                                               ; preds = %3
//   call void (...) @gl_flush()
//   ret void
    builder->SetInsertPoint(id2bb[24]);
    auto gl_flushFunc = module->getFunction("gl_flush");
    builder->CreateCall(gl_flushFunc);
    builder->CreateRetVoid();
}

void timf_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& timfFunc = module->getFunction("timf");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", timfFunc);
    builder->SetInsertPoint(entry);
    id2value[0] = timfFunc->getArg(0);
    id2bb[5] = llvm::BasicBlock::Create(module->getContext(), "5", timfFunc );
    id2bb[8] = llvm::BasicBlock::Create(module->getContext(), "8", timfFunc );
    id2bb[9] = llvm::BasicBlock::Create(module->getContext(), "9", timfFunc );
    id2bb[10] = llvm::BasicBlock::Create(module->getContext(), "10", timfFunc );
    id2bb[11] = llvm::BasicBlock::Create(module->getContext(), "11", timfFunc );

//   %2 = alloca i32, align 4
//   store i32 %0, i32* %2, align 4
//   %3 = load i32, i32* @flag_no_recalc, align 4
//   %4 = icmp eq i32 %3, 0
//   br i1 %4, label %5, label %11

    id2value[2] = builder->CreateAlloca(builder->getInt32Ty());
    builder->CreateStore(id2value[0], id2value[2]);
    auto flag_no_recalc = module->getNamedGlobal ("flag_no_recalc");
    id2value[3] = builder->CreateLoad(builder->getInt32Ty(), flag_no_recalc);
    id2value[4] = builder->CreateICmpEQ(id2value[3], llvm::ConstantInt::get(builder->getInt32Ty(), 0));
    builder->CreateCondBr(id2value[4], id2bb[5], id2bb[11]);

// 5:                                                ; preds = %1
//   %6 = call i32 @calc_new_centers()
//   %7 = icmp slt i32 %6, 20
//   br i1 %7, label %8, label %9
    builder->SetInsertPoint(id2bb[5]);
    auto calc_new_centersFunc = module->getFunction("calc_new_centers");
    id2value[6] = builder->CreateCall(calc_new_centersFunc);
    id2value[7] = builder->CreateICmpSLT(id2value[6], llvm::ConstantInt::get(builder->getInt32Ty(), 20));
    builder->CreateCondBr(id2value[7], id2bb[8], id2bb[9]);


// 8:                                                ; preds = %5
//   call void @display()
//   br label %10

    builder->SetInsertPoint(id2bb[8]);
    auto displayFunc = module->getFunction("display");
    builder->CreateCall(displayFunc);
    builder->CreateBr(id2bb[10]);


// 9:                                                ; preds = %5
//   store i32 1, i32* @flag_no_recalc, align 4
//   br label %10
    builder->SetInsertPoint(id2bb[9]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 1), flag_no_recalc);
    builder->CreateBr(id2bb[10]);


// 10:                                               ; preds = %9, %8
//   br label %11

    builder->SetInsertPoint(id2bb[10]);
    builder->CreateBr(id2bb[11]);

// 11:                                               ; preds = %10, %1
//   %12 = load i32, i32* %2, align 4
//   call void @set_timer(i32 %12)
//   ret void
    builder->SetInsertPoint(id2bb[11]);
    id2value[12] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    auto set_timerFunc = module->getFunction("set_timer");
    builder->CreateCall(set_timerFunc);
    builder->CreateRetVoid();
}

void calc_new_centers_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& calc_new_centersFunc = module->getFunction("calc_new_centers");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", calc_new_centersFunc);
    builder->SetInsertPoint(entry);
    llvm::ArrayType* ar10 = llvm::ArrayType::get(builder->getInt32Ty(), 10);
    llvm::StructType* Point = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());

    id2bb[10] = llvm::BasicBlock::Create(module->getContext(), "10", calc_new_centersFunc );
    id2bb[13] = llvm::BasicBlock::Create(module->getContext(), "13", calc_new_centersFunc );
    id2bb[23] = llvm::BasicBlock::Create(module->getContext(), "23", calc_new_centersFunc );
    id2bb[26] = llvm::BasicBlock::Create(module->getContext(), "26", calc_new_centersFunc );
    id2bb[27] = llvm::BasicBlock::Create(module->getContext(), "27", calc_new_centersFunc );
    id2bb[30] = llvm::BasicBlock::Create(module->getContext(), "30", calc_new_centersFunc );
    id2bb[31] = llvm::BasicBlock::Create(module->getContext(), "31", calc_new_centersFunc );
    id2bb[34] = llvm::BasicBlock::Create(module->getContext(), "34", calc_new_centersFunc );
    id2bb[44] = llvm::BasicBlock::Create(module->getContext(), "44", calc_new_centersFunc );
    id2bb[97] = llvm::BasicBlock::Create(module->getContext(), "97", calc_new_centersFunc );
    id2bb[98] = llvm::BasicBlock::Create(module->getContext(), "98", calc_new_centersFunc );
    id2bb[101] = llvm::BasicBlock::Create(module->getContext(), "101", calc_new_centersFunc );
    id2bb[102] = llvm::BasicBlock::Create(module->getContext(), "102", calc_new_centersFunc );
    id2bb[105] = llvm::BasicBlock::Create(module->getContext(), "105", calc_new_centersFunc );
    id2bb[106] = llvm::BasicBlock::Create(module->getContext(), "106", calc_new_centersFunc );
    id2bb[109] = llvm::BasicBlock::Create(module->getContext(), "109", calc_new_centersFunc );
    id2bb[126] = llvm::BasicBlock::Create(module->getContext(), "126", calc_new_centersFunc );
    id2bb[129] = llvm::BasicBlock::Create(module->getContext(), "129", calc_new_centersFunc );
    id2bb[135] = llvm::BasicBlock::Create(module->getContext(), "135", calc_new_centersFunc );
    id2bb[152] = llvm::BasicBlock::Create(module->getContext(), "152", calc_new_centersFunc );
    id2bb[155] = llvm::BasicBlock::Create(module->getContext(), "155", calc_new_centersFunc );
    id2bb[161] = llvm::BasicBlock::Create(module->getContext(), "161", calc_new_centersFunc );
    id2bb[162] = llvm::BasicBlock::Create(module->getContext(), "162", calc_new_centersFunc );
    id2bb[165] = llvm::BasicBlock::Create(module->getContext(), "165", calc_new_centersFunc );

//   %1 = alloca i32, align 4
//   %2 = alloca i32, align 4
//   %3 = alloca [10 x i32], align 16
//   %4 = alloca [10 x i32], align 16
//   %5 = alloca [10 x i32], align 16
//   %6 = alloca i32, align 4
//   %7 = alloca i32, align 4
//   %8 = alloca i32, align 4
//   %9 = alloca i32, align 4
//   store i32 0, i32* %1, align 4
//   store i32 0, i32* %2, align 4
//   store i32 0, i32* %6, align 4
//   br label %10

    id2value[1] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[2] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[3] = builder->CreateAlloca(ar10);
    id2value[4] = builder->CreateAlloca(ar10);
    id2value[5] = builder->CreateAlloca(ar10);
    id2value[6] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[7] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[8] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[9] = builder->CreateAlloca(builder->getInt32Ty());
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[1]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[2]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[6]);
    builder->CreateBr(id2bb[10]);

// 10:                                               ; preds = %23, %0
//   %11 = load i32, i32* %6, align 4
//   %12 = icmp slt i32 %11, 10
//   br i1 %12, label %13, label %26


    builder->SetInsertPoint(id2bb[10]);
    id2value[11] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[12] = builder->CreateICmpSLT(id2value[11], llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    builder->CreateCondBr(id2value[11], id2bb[13], id2bb[26]);

// 13:                                               ; preds = %10
//   %14 = load i32, i32* %6, align 4
//   %15 = sext i32 %14 to i64
//   %16 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %15
//   store i32 0, i32* %16, align 4
//   %17 = load i32, i32* %6, align 4
//   %18 = sext i32 %17 to i64
//   %19 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %18
//   store i32 0, i32* %19, align 4
//   %20 = load i32, i32* %6, align 4
//   %21 = sext i32 %20 to i64
//   %22 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %21
//   store i32 0, i32* %22, align 4
//   br label %23

    builder->SetInsertPoint(id2bb[13]);
    id2value[14] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[15] = builder->CreateSExt(id2value[14], builder->getInt64Ty());
    auto&& pixels = module->getNamedGlobal ("pixels");
    auto&& points = module->getNamedGlobal ("points");

    id2value[16] = builder->CreateInBoundsGEP(ar10, id2value[3], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[15]});
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2value[16]);
    id2value[17] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[18] = builder->CreateSExt(id2value[17], builder->getInt64Ty());
    id2value[19] = builder->CreateInBoundsGEP(ar10, id2value[4], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[18]});
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2value[19]);
    id2value[20] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[21] = builder->CreateSExt(id2value[20], builder->getInt64Ty());
    id2value[22] = builder->CreateInBoundsGEP(ar10, id2value[5], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[21]});
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2value[22]);
    builder->CreateBr(id2bb[23]);

// 23:                                               ; preds = %13
//   %24 = load i32, i32* %6, align 4
//   %25 = add nsw i32 %24, 1
//   store i32 %25, i32* %6, align 4
//   br label %10

    builder->SetInsertPoint(id2bb[23]);
    id2value[24] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[25] = builder->CreateNSWAdd(id2value[24], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    builder->CreateStore(id2value[25], id2value[6]);
    builder->CreateBr(id2bb[10]);


// 26:                                               ; preds = %10
//   store i32 0, i32* %7, align 4
//   br label %27

    builder->SetInsertPoint(id2bb[26]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0) , id2value[7]);
    builder->CreateBr(id2bb[27]);

// 27:                                               ; preds = %102, %26
//   %28 = load i32, i32* %7, align 4
//   %29 = icmp slt i32 %28, 800
//   br i1 %29, label %30, label %105

    builder->SetInsertPoint(id2bb[27]);
    id2value[28] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[29] = builder->CreateICmpSLT(id2value[28], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateCondBr(id2value[29], id2bb[30], id2bb[105]);

// 30:                                               ; preds = %27
//   store i32 0, i32* %8, align 4
//   br label %31

    builder->SetInsertPoint(id2bb[30]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[8]);
    builder->CreateBr(id2bb[31]);

// 31:                                               ; preds = %98, %30
//   %32 = load i32, i32* %8, align 4
//   %33 = icmp slt i32 %32, 800
//   br i1 %33, label %34, label %101

    builder->SetInsertPoint(id2bb[31]);
    id2value[32] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[33] = builder->CreateICmpSLT(id2value[32], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateCondBr(id2value[33], id2bb[34], id2bb[101]);

// 34:                                               ; preds = %31
//   %35 = load i32, i32* %7, align 4
//   %36 = sext i32 %35 to i64
//   %37 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %36
//   %38 = load i32, i32* %8, align 4
//   %39 = sext i32 %38 to i64
//   %40 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %37, i64 0, i64 %39
//   %41 = getelementptr inbounds %struct.Point, %struct.Point* %40, i32 0, i32 0
//   %42 = load i32, i32* %41, align 4
//   %43 = icmp sge i32 %42, 0
//   br i1 %43, label %44, label %97

    builder->SetInsertPoint(id2bb[34]);
    id2value[35] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[36] = builder->CreateSExt(id2value[35], builder->getInt64Ty());
    id2value[37] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[36]});
    id2value[38] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[39] = builder->CreateSExt(id2value[38], builder->getInt64Ty());
    id2value[40] = builder->CreateInBoundsGEP(pixels_subtype, id2value[37], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[39]});
    id2value[41] = builder->CreateInBoundsGEP(Point, id2value[40], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 0)});
    id2value[42] = builder->CreateLoad(builder->getInt32Ty(), id2value[41]);
    id2value[43] = builder->CreateICmpSGE(id2value[42], llvm::ConstantInt::get(builder->getInt32Ty(), 0));
    builder->CreateCondBr(id2value[43], id2bb[44], id2bb[97]);


// 44:                                               ; preds = %34
//   %45 = load i32, i32* %7, align 4
//   %46 = sext i32 %45 to i64
//   %47 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %46
//   %48 = load i32, i32* %8, align 4
//   %49 = sext i32 %48 to i64
//   %50 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %47, i64 0, i64 %49
//   %51 = getelementptr inbounds %struct.Point, %struct.Point* %50, i32 0, i32 1
//   %52 = load i32, i32* %51, align 4
//   %53 = load i32, i32* %7, align 4
//   %54 = sext i32 %53 to i64

    builder->SetInsertPoint(id2bb[44]);
    id2value[45] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[46] = builder->CreateSExt(id2value[45], builder->getInt64Ty());
    id2value[47] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[46]});
    id2value[48] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[49] = builder->CreateSExt(id2value[48], builder->getInt64Ty());
    id2value[50] = builder->CreateInBoundsGEP(pixels_subtype, id2value[47], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[49]});
    id2value[51] = builder->CreateInBoundsGEP(Point, id2value[50], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)});
    id2value[52] = builder->CreateLoad(builder->getInt32Ty(), id2value[41]);
    id2value[53] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[54] = builder->CreateSExt(id2value[53], builder->getInt64Ty());


//   %55 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %54
//   %56 = load i32, i32* %8, align 4
//   %57 = sext i32 %56 to i64
//   %58 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %55, i64 0, i64 %57
//   %59 = getelementptr inbounds %struct.Point, %struct.Point* %58, i32 0, i32 0
//   %60 = load i32, i32* %59, align 4
//   %61 = sext i32 %60 to i64


    id2value[55] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[54]});
    id2value[56] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[57] = builder->CreateSExt(id2value[56], builder->getInt64Ty());
    id2value[58] = builder->CreateInBoundsGEP(pixels_subtype, id2value[55], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[57]});
    id2value[59] = builder->CreateInBoundsGEP(Point, id2value[58], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 0)});
    id2value[60] = builder->CreateLoad(builder->getInt32Ty(), id2value[59]);
    id2value[61] = builder->CreateSExt(id2value[60], builder->getInt64Ty());


//   %62 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %61
//   %63 = load i32, i32* %62, align 4
//   %64 = add nsw i32 %63, %52
//   store i32 %64, i32* %62, align 4
//   %65 = load i32, i32* %7, align 4
//   %66 = sext i32 %65 to i64

    id2value[62] = builder->CreateInBoundsGEP(ar10, id2value[3], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[61]});
    id2value[63] = builder->CreateLoad(builder->getInt32Ty(), id2value[62]);
    id2value[64] = builder->CreateNSWAdd(id2value[63], id2value[52]);
    builder->CreateStore(id2value[64] , id2value[62]);
    id2value[65] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[66] = builder->CreateSExt(id2value[65], builder->getInt64Ty());




//   %67 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %66
//   %68 = load i32, i32* %8, align 4
//   %69 = sext i32 %68 to i64
//   %70 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %67, i64 0, i64 %69
//   %71 = getelementptr inbounds %struct.Point, %struct.Point* %70, i32 0, i32 2
//   %72 = load i32, i32* %71, align 4
//   %73 = load i32, i32* %7, align 4
//   %74 = sext i32 %73 to i64

    id2value[67] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[66]});
    id2value[68] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[69] = builder->CreateSExt(id2value[48], builder->getInt64Ty());
    id2value[70] = builder->CreateInBoundsGEP(pixels_subtype, id2value[67], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[69]});
    id2value[71] = builder->CreateInBoundsGEP(Point, id2value[70], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)});
    id2value[72] = builder->CreateLoad(builder->getInt32Ty(), id2value[71]);
    id2value[73] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[74] = builder->CreateSExt(id2value[73], builder->getInt64Ty());


//   %75 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %74
//   %76 = load i32, i32* %8, align 4
//   %77 = sext i32 %76 to i64
//   %78 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %75, i64 0, i64 %77
//   %79 = getelementptr inbounds %struct.Point, %struct.Point* %78, i32 0, i32 0
//   %80 = load i32, i32* %79, align 4
//   %81 = sext i32 %80 to i64


    id2value[75] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[74]});
    id2value[76] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[77] = builder->CreateSExt(id2value[76], builder->getInt64Ty());
    id2value[78] = builder->CreateInBoundsGEP(pixels_subtype, id2value[75], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[77]});
    id2value[79] = builder->CreateInBoundsGEP(Point, id2value[78], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 0)});
    id2value[80] = builder->CreateLoad(builder->getInt32Ty(), id2value[79]);
    id2value[81] = builder->CreateSExt(id2value[80], builder->getInt64Ty());

//   %82 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %81
//   %83 = load i32, i32* %82, align 4
//   %84 = add nsw i32 %83, %72
//   store i32 %84, i32* %82, align 4
//   %85 = load i32, i32* %7, align 4
//   %86 = sext i32 %85 to i64

    id2value[82] = builder->CreateInBoundsGEP(ar10, id2value[4], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[81]});
    id2value[83] = builder->CreateLoad(builder->getInt32Ty(), id2value[82]);
    id2value[84] = builder->CreateNSWAdd(id2value[83], id2value[72]);
    builder->CreateStore(id2value[64] , id2value[82]);
    id2value[85] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[86] = builder->CreateSExt(id2value[85], builder->getInt64Ty());

//   %87 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %86
//   %88 = load i32, i32* %8, align 4
//   %89 = sext i32 %88 to i64
//   %90 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %87, i64 0, i64 %89
//   %91 = getelementptr inbounds %struct.Point, %struct.Point* %90, i32 0, i32 0
//   %92 = load i32, i32* %91, align 4
//   %93 = sext i32 %92 to i64
//   %94 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %93
//   %95 = load i32, i32* %94, align 4
//   %96 = add nsw i32 %95, 1
//   store i32 %96, i32* %94, align 4
//   br label %97

    id2value[87] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[86]});
    id2value[88] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[89] = builder->CreateSExt(id2value[88], builder->getInt64Ty());
    id2value[90] = builder->CreateInBoundsGEP(pixels_subtype, id2value[87], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[89]});
    id2value[91] = builder->CreateInBoundsGEP(Point, id2value[90], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 0)});
    id2value[92] = builder->CreateLoad(builder->getInt32Ty(), id2value[91]);
    id2value[93] = builder->CreateSExt(id2value[92], builder->getInt64Ty());

    id2value[94] = builder->CreateInBoundsGEP(ar10, id2value[5], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[93]});
    id2value[95] = builder->CreateLoad(builder->getInt32Ty(), id2value[94]);
    id2value[96] = builder->CreateNSWAdd(id2value[95], llvm::ConstantInt::get(builder->getInt32Ty(), 1));
    builder->CreateStore(id2value[96] , id2value[94]);
    builder->CreateBr(id2bb[97]);

// 97:                                               ; preds = %44, %34
//   br label %98

    builder->SetInsertPoint(id2bb[97]);
    builder->CreateBr(id2bb[98]);

// 98:                                               ; preds = %97
//   %99 = load i32, i32* %8, align 4
//   %100 = add nsw i32 %99, 1
//   store i32 %100, i32* %8, align 4
//   br label %31

    builder->SetInsertPoint(id2bb[98]);
    id2value[99] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[100] = builder->CreateNSWAdd(id2value[99], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    builder->CreateStore(id2value[100], id2value[8]);
    builder->CreateBr(id2bb[31]);

// 101:                                              ; preds = %31
//   br label %102

    builder->SetInsertPoint(id2bb[101]);
    builder->CreateBr(id2bb[102]);

// 102:                                              ; preds = %101
//   %103 = load i32, i32* %7, align 4
//   %104 = add nsw i32 %103, 1
//   store i32 %104, i32* %7, align 4
//   br label %27

    builder->SetInsertPoint(id2bb[102]);
    id2value[103] = builder->CreateLoad(builder->getInt32Ty(), id2value[7]);
    id2value[104] = builder->CreateNSWAdd(id2value[103], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    builder->CreateStore(id2value[104], id2value[7]);
    builder->CreateBr(id2bb[27]);

// 105:                                              ; preds = %27
//   store i32 0, i32* %9, align 4
//   br label %106

    builder->SetInsertPoint(id2bb[105]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[9]);
    builder->CreateBr(id2bb[106]);

// 106:                                              ; preds = %162, %105
//   %107 = load i32, i32* %9, align 4
//   %108 = icmp slt i32 %107, 10
//   br i1 %108, label %109, label %165

    builder->SetInsertPoint(id2bb[106]);
    id2value[107] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[108] = builder->CreateICmpSLT(id2value[107], llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    builder->CreateCondBr(id2value[108], id2bb[109], id2bb[165]);

// 109:                                              ; preds = %106
//   %110 = load i32, i32* %9, align 4
//   %111 = sext i32 %110 to i64
//   %112 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %111
//   %113 = load i32, i32* %112, align 4
//   %114 = load i32, i32* %9, align 4
//   %115 = sext i32 %114 to i64
//   %116 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %115
//   %117 = load i32, i32* %116, align 4
//   %118 = sdiv i32 %113, %117
//   store i32 %118, i32* %2, align 4
//   %119 = load i32, i32* %9, align 4
//   %120 = sext i32 %119 to i64
//   %121 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %120
//   %122 = getelementptr inbounds %struct.Point, %struct.Point* %121, i32 0, i32 1
//   %123 = load i32, i32* %122, align 4
//   %124 = load i32, i32* %2, align 4
//   %125 = icmp eq i32 %123, %124
//   br i1 %125, label %126, label %129


    builder->SetInsertPoint(id2bb[109]);
    id2value[110] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[111] = builder->CreateSExt(id2value[110], builder->getInt64Ty());
    id2value[112] = builder->CreateInBoundsGEP(ar10, id2value[3], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[111]});
    id2value[113] = builder->CreateLoad(builder->getInt32Ty(), id2value[112]);
    id2value[114] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[115] = builder->CreateSExt(id2value[114], builder->getInt64Ty());
    id2value[116] = builder->CreateInBoundsGEP(ar10, id2value[5], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[115]});
    id2value[117] = builder->CreateLoad(builder->getInt32Ty(), id2value[116]);
    id2value[118] = builder->CreateSDiv(id2value[113], id2value[117]);
    builder->CreateStore(id2value[118], id2value[2]);
    id2value[119] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[120] = builder->CreateSExt(id2value[119], builder->getInt64Ty());
    id2value[121] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[120]});
    id2value[122] = builder->CreateInBoundsGEP(Point, id2value[121], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)});
    id2value[123] = builder->CreateLoad(builder->getInt32Ty(), id2value[122]);
    id2value[124] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[125] = builder->CreateICmpEQ(id2value[123], id2value[124]);
    builder->CreateCondBr(id2value[125], id2bb[126], id2bb[129]);

// 126:                                              ; preds = %109
//   %127 = load i32, i32* %1, align 4
//   %128 = add nsw i32 %127, 1
//   store i32 %128, i32* %1, align 4
//   br label %135

    builder->SetInsertPoint(id2bb[126]);
    id2value[127] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[128] = builder->CreateNSWAdd(id2value[127], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    builder->CreateStore(id2value[128], id2value[1]);
    builder->CreateBr(id2bb[135]);

// 129:                                              ; preds = %109
//   %130 = load i32, i32* %2, align 4
//   %131 = load i32, i32* %9, align 4
//   %132 = sext i32 %131 to i64
//   %133 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %132
//   %134 = getelementptr inbounds %struct.Point, %struct.Point* %133, i32 0, i32 1
//   store i32 %130, i32* %134, align 4
//   br label %135

    builder->SetInsertPoint(id2bb[129]);
    id2value[130] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[131] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[132] = builder->CreateSExt(id2value[131], builder->getInt64Ty());
    id2value[133] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[132]});
    id2value[134] = builder->CreateInBoundsGEP(Point, id2value[133], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)});
    builder->CreateStore(id2value[130], id2value[134]);
    builder->CreateBr(id2bb[135]);

  

// 135:                                              ; preds = %129, %126
//   %136 = load i32, i32* %9, align 4
//   %137 = sext i32 %136 to i64
//   %138 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %137
//   %139 = load i32, i32* %138, align 4
//   %140 = load i32, i32* %9, align 4
//   %141 = sext i32 %140 to i64
//   %142 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %141
//   %143 = load i32, i32* %142, align 4
//   %144 = sdiv i32 %139, %143
//   store i32 %144, i32* %2, align 4
//   %145 = load i32, i32* %9, align 4
//   %146 = sext i32 %145 to i64
//   %147 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %146
//   %148 = getelementptr inbounds %struct.Point, %struct.Point* %147, i32 0, i32 2
//   %149 = load i32, i32* %148, align 4
//   %150 = load i32, i32* %2, align 4
//   %151 = icmp eq i32 %149, %150
//   br i1 %151, label %152, label %155


 builder->SetInsertPoint(id2bb[135]);
    id2value[136] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[137] = builder->CreateSExt(id2value[136], builder->getInt64Ty());
    id2value[138] = builder->CreateInBoundsGEP(ar10, id2value[4], {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[137]});
    id2value[139] = builder->CreateLoad(builder->getInt32Ty(), id2value[138]);
    id2value[140] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[141] = builder->CreateSExt(id2value[140], builder->getInt64Ty());
    id2value[142] = builder->CreateInBoundsGEP(ar10, id2value[5], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[141]});
    id2value[143] = builder->CreateLoad(builder->getInt32Ty(), id2value[142]);
    id2value[144] = builder->CreateSDiv(id2value[139], id2value[143]);
    builder->CreateStore(id2value[144], id2value[2]);
    id2value[145] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[146] = builder->CreateSExt(id2value[145], builder->getInt64Ty());
    id2value[147] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[146]});
    id2value[148] = builder->CreateInBoundsGEP(Point, id2value[147], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)});
    id2value[149] = builder->CreateLoad(builder->getInt32Ty(), id2value[148]);
    id2value[150] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[151] = builder->CreateICmpEQ(id2value[149], id2value[150]);
    builder->CreateCondBr(id2value[151], id2bb[152], id2bb[155]);


// 152:                                              ; preds = %135
//   %153 = load i32, i32* %1, align 4
//   %154 = add nsw i32 %153, 1
//   store i32 %154, i32* %1, align 4
//   br label %161

    builder->SetInsertPoint(id2bb[152]);
    id2value[153] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[154] = builder->CreateNSWAdd(id2value[153], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    builder->CreateStore(id2value[154], id2value[1]);
    builder->CreateBr(id2bb[161]);

// 155:                                              ; preds = %135
//   %156 = load i32, i32* %2, align 4
//   %157 = load i32, i32* %9, align 4
//   %158 = sext i32 %157 to i64
//   %159 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %158
//   %160 = getelementptr inbounds %struct.Point, %struct.Point* %159, i32 0, i32 2
//   store i32 %156, i32* %160, align 4
//   br label %161

    builder->SetInsertPoint(id2bb[155]);
    id2value[156] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[157] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[158] = builder->CreateSExt(id2value[131], builder->getInt64Ty());
    id2value[159] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[158]});
    id2value[160] = builder->CreateInBoundsGEP(Point, id2value[159], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)});
    builder->CreateStore(id2value[156], id2value[160]);
    builder->CreateBr(id2bb[161]);


// 161:                                              ; preds = %155, %152
//   br label %162

    builder->SetInsertPoint(id2bb[161]);
    builder->CreateBr(id2bb[162]);

// 162:                                              ; preds = %161
//   %163 = load i32, i32* %9, align 4
//   %164 = add nsw i32 %163, 1
//   store i32 %164, i32* %9, align 4
//   br label %106

    builder->SetInsertPoint(id2bb[162]);
    id2value[163] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[164] = builder->CreateNSWAdd(id2value[163], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    builder->CreateStore(id2value[164], id2value[9]);
    builder->CreateBr(id2bb[106]);

// 165:                                              ; preds = %106
//   %166 = load i32, i32* %1, align 4
//   ret i32 %166
    builder->SetInsertPoint(id2bb[165]);
    id2value[166] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    builder->CreateRet(id2value[166]);

}

void set_timer_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& set_timerFunc = module->getFunction("set_timer");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", set_timerFunc);
    builder->SetInsertPoint(entry);
    id2value[0] = set_timerFunc->getArg(0);

//   %2 = alloca i32, align 4
//   store i32 %0, i32* %2, align 4
//   ret void

    id2value[2] = builder->CreateAlloca(builder->getInt32Ty());
    builder->CreateStore(id2value[0], id2value[2]);
    builder->CreateRetVoid();
}

void calc_vor_diag_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& calc_vor_diagFunc = module->getFunction("calc_vor_diag");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", calc_vor_diagFunc);
    builder->SetInsertPoint(entry);

    id2bb[6] = llvm::BasicBlock::Create(module->getContext(), "6", calc_vor_diagFunc );
    id2bb[9] = llvm::BasicBlock::Create(module->getContext(), "9", calc_vor_diagFunc );
    id2bb[10] = llvm::BasicBlock::Create(module->getContext(), "10", calc_vor_diagFunc );
    id2bb[13] = llvm::BasicBlock::Create(module->getContext(), "13", calc_vor_diagFunc );
    id2bb[14] = llvm::BasicBlock::Create(module->getContext(), "14", calc_vor_diagFunc );
    id2bb[17] = llvm::BasicBlock::Create(module->getContext(), "17", calc_vor_diagFunc );
    id2bb[20] = llvm::BasicBlock::Create(module->getContext(), "20", calc_vor_diagFunc );
    id2bb[22] = llvm::BasicBlock::Create(module->getContext(), "22", calc_vor_diagFunc );
    id2bb[35] = llvm::BasicBlock::Create(module->getContext(), "35", calc_vor_diagFunc );
    id2bb[45] = llvm::BasicBlock::Create(module->getContext(), "45", calc_vor_diagFunc );
    id2bb[46] = llvm::BasicBlock::Create(module->getContext(), "46", calc_vor_diagFunc );
    id2bb[49] = llvm::BasicBlock::Create(module->getContext(), "49", calc_vor_diagFunc );
    id2bb[50] = llvm::BasicBlock::Create(module->getContext(), "50", calc_vor_diagFunc );
    id2bb[69] = llvm::BasicBlock::Create(module->getContext(), "69", calc_vor_diagFunc );
    id2bb[70] = llvm::BasicBlock::Create(module->getContext(), "70", calc_vor_diagFunc );
    id2bb[73] = llvm::BasicBlock::Create(module->getContext(), "73", calc_vor_diagFunc );

//  %1 = alloca i32, align 4
//   %2 = alloca i32, align 4
//   %3 = alloca i32, align 4
//   %4 = alloca i32, align 4
//   %5 = alloca i32, align 4
//   store i32 0, i32* %1, align 4
//   br label %6

    id2value[1] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[2] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[3] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[4] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[5] = builder->CreateAlloca(builder->getInt32Ty());
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[1]);
    builder->CreateBr(id2bb[6]);

// 6:                                                ; preds = %70, %0
//   %7 = load i32, i32* %1, align 4
//   %8 = icmp slt i32 %7, 800
//   br i1 %8, label %9, label %73

    builder->SetInsertPoint(id2bb[6]);
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[8] = builder->CreateICmpSLT(id2value[7], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateCondBr(id2value[8], id2bb[9], id2bb[73]);
// 9:                                                ; preds = %6
//   store i32 0, i32* %2, align 4
//   store i32 1000000000, i32* %3, align 4
//   br label %10

    builder->SetInsertPoint(id2bb[9]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[2]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 1000000000), id2value[3]);
    builder->CreateBr(id2bb[10]);

// 10:                                               ; preds = %50, %9
//   %11 = load i32, i32* %2, align 4
//   %12 = icmp slt i32 %11, 800
//   br i1 %12, label %13, label %69

    builder->SetInsertPoint(id2bb[10]);
    id2value[11] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[12] = builder->CreateICmpSLT(id2value[11], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateCondBr(id2value[12], id2bb[13], id2bb[69]);

// 13:                                               ; preds = %10
//   store i32 0, i32* %4, align 4
//   store i32 0, i32* %5, align 4
//   br label %14

    builder->SetInsertPoint(id2bb[13]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[4]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[5]);
    builder->CreateBr(id2bb[14]);

// 14:                                               ; preds = %46, %13
//   %15 = load i32, i32* %4, align 4
//   %16 = icmp slt i32 %15, 10
//   br i1 %16, label %17, label %20

    builder->SetInsertPoint(id2bb[14]);
    id2value[15] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[16] = builder->CreateICmpSLT(id2value[15], llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    builder->CreateCondBr(id2value[16], id2bb[17], id2bb[20]);

// 17:                                               ; preds = %14
//   %18 = load i32, i32* %3, align 4
//   %19 = icmp sgt i32 %18, 0
//   br label %20

    builder->SetInsertPoint(id2bb[17]);
    id2value[18] = builder->CreateLoad(builder->getInt32Ty(), id2value[3]);
    id2value[19] = builder->CreateICmpSLT(id2value[11], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    builder->CreateBr(id2bb[20]);

// 20:                                               ; preds = %17, %14
//   %21 = phi i1 [ false, %14 ], [ %19, %17 ]
//   br i1 %21, label %22, label %49

    builder->SetInsertPoint(id2bb[20]);
    auto&& phiNode = builder->CreatePHI(builder->getInt1Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt1Ty(), 0), id2bb[14]);
    phiNode->addIncoming(id2value[19], id2bb[17]);
    id2value[21] = phiNode;
    builder->CreateCondBr(id2value[21], id2bb[22], id2bb[49]);

// 22:                                               ; preds = %20
//   %23 = load i32, i32* %1, align 4
//   %24 = sext i32 %23 to i64
//   %25 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %24
//   %26 = load i32, i32* %2, align 4
//   %27 = sext i32 %26 to i64
//   %28 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %25, i64 0, i64 %27
//   %29 = load i32, i32* %4, align 4
//   %30 = sext i32 %29 to i64
//   %31 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %30
//   %32 = call i32 @dist(%struct.Point* %28, %struct.Point* %31)
//   store i32 %32, i32* %5, align 4
//   %33 = load i32, i32* %3, align 4
//   %34 = icmp slt i32 %32, %33
//   br i1 %34, label %35, label %45
    llvm::StructType* Point = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());

    builder->SetInsertPoint(id2bb[22]);
    id2value[23] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[24] = builder->CreateSExt(id2value[23], builder->getInt64Ty());
    auto&& pixels = module->getNamedGlobal ("pixels");
    auto&& points = module->getNamedGlobal ("points");
llvm::ArrayType* pixels_subtype = llvm::ArrayType::get(Point, 800);
    id2value[25] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[24]});
    id2value[26] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[27] = builder->CreateSExt(id2value[26], builder->getInt64Ty());
    id2value[28] = builder->CreateInBoundsGEP(pixels_subtype, id2value[25], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[27]});
    id2value[29] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[30] = builder->CreateSExt(id2value[29], builder->getInt64Ty());
    id2value[31] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[30]});
    auto distFunc = module->getFunction("dist");
    id2value[32] = builder->CreateCall(distFunc, {id2value[28], id2value[31]});
    builder->CreateStore(id2value[32], id2value[5]);
    id2value[33] = builder->CreateLoad(builder->getInt32Ty(), id2value[3]);
    id2value[34] = builder->CreateICmpSLT(id2value[32], id2value[33]);
    builder->CreateCondBr(id2value[34], id2bb[35], id2bb[45]);



// 35:                                               ; preds = %22
//   %36 = load i32, i32* %5, align 4
//   store i32 %36, i32* %3, align 4
//   %37 = load i32, i32* %4, align 4
//   %38 = load i32, i32* %1, align 4
//   %39 = sext i32 %38 to i64
//   %40 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %39
//   %41 = load i32, i32* %2, align 4
//   %42 = sext i32 %41 to i64
//   %43 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %40, i64 0, i64 %42
//   %44 = getelementptr inbounds %struct.Point, %struct.Point* %43, i32 0, i32 0
//   store i32 %37, i32* %44, align 4
//   br label %45

    builder->SetInsertPoint(id2bb[35]);
    id2value[36] = builder->CreateLoad(builder->getInt32Ty(), id2value[5]);
    builder->CreateStore(id2value[36], id2value[3]);
    id2value[37] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[38] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[39] = builder->CreateSExt(id2value[23], builder->getInt64Ty());
    id2value[40] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[39]});
    id2value[41] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[42] = builder->CreateSExt(id2value[41], builder->getInt64Ty());
    id2value[43] = builder->CreateInBoundsGEP(pixels_subtype, id2value[40], {llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[42]});
    id2value[44] = builder->CreateInBoundsGEP(Point, id2value[43], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) ,llvm::ConstantInt::get(builder->getInt32Ty(), 0)  });
    builder->CreateStore(id2value[37], id2value[44]);
    builder->CreateBr(id2bb[45]);

   

// 45:                                               ; preds = %35, %22
//   br label %46
    builder->SetInsertPoint(id2bb[45]);
    builder->CreateBr(id2bb[46]);


// 46:                                               ; preds = %45
//   %47 = load i32, i32* %4, align 4
//   %48 = add nsw i32 %47, 1
//   store i32 %48, i32* %4, align 4
//   br label %14
    builder->SetInsertPoint(id2bb[46]);
    id2value[47] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[48] = builder->CreateNSWAdd(id2value[47], llvm::ConstantInt::get(builder->getInt64Ty(), 1) );
    builder->CreateStore(id2value[48], id2value[4]);
    builder->CreateBr(id2bb[14]);


// 49:                                               ; preds = %20
//   br label %50
    builder->SetInsertPoint(id2bb[49]);
    builder->CreateBr(id2bb[50]);

// 50:                                               ; preds = %49
//   %51 = load i32, i32* %2, align 4
//   %52 = load i32, i32* %1, align 4
//   %53 = sext i32 %52 to i64
//   %54 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %53
//   %55 = load i32, i32* %2, align 4
//   %56 = sext i32 %55 to i64
//   %57 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %54, i64 0, i64 %56
//   %58 = getelementptr inbounds %struct.Point, %struct.Point* %57, i32 0, i32 1
//   store i32 %51, i32* %58, align 4
//   %59 = load i32, i32* %1, align 4
//   %60 = load i32, i32* %1, align 4
//   %61 = sext i32 %60 to i64
//   %62 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %61
//   %63 = load i32, i32* %2, align 4
//   %64 = sext i32 %63 to i64
//   %65 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %62, i64 0, i64 %64
//   %66 = getelementptr inbounds %struct.Point, %struct.Point* %65, i32 0, i32 2
//   store i32 %59, i32* %66, align 4
//   %67 = load i32, i32* %2, align 4
//   %68 = add nsw i32 %67, 1
//   store i32 %68, i32* %2, align 4
//   store i32 1000000000, i32* %3, align 4
//   br label %10
    std::cout << "bef 50 calc vor diag" << std::endl;

    builder->SetInsertPoint(id2bb[50]);
    id2value[51] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[52] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[53] = builder->CreateSExt(id2value[52], builder->getInt64Ty());
    id2value[54] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[53]});
    id2value[55] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[56] = builder->CreateSExt(id2value[55], builder->getInt64Ty());
    id2value[57] = builder->CreateInBoundsGEP(pixels_subtype, id2value[54], {llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[56]});
    id2value[58] = builder->CreateInBoundsGEP(Point, id2value[57], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) ,llvm::ConstantInt::get(builder->getInt32Ty(), 1)  });
    builder->CreateStore(id2value[51], id2value[58]);

    id2value[59] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[60] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[61] = builder->CreateSExt(id2value[60], builder->getInt64Ty());
    id2value[62] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[61]});
    id2value[63] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[64] = builder->CreateSExt(id2value[63], builder->getInt64Ty());

    id2value[65] = builder->CreateInBoundsGEP(pixels_subtype, id2value[62], {llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[64]});
    id2value[66] = builder->CreateInBoundsGEP(Point, id2value[65], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) ,llvm::ConstantInt::get(builder->getInt32Ty(), 2)  });
    builder->CreateStore(id2value[59], id2value[66]);

    id2value[67] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[68] = builder->CreateNSWAdd(id2value[67], llvm::ConstantInt::get(builder->getInt32Ty(), 1));
    builder->CreateStore(id2value[68], id2value[2]);
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 1000000000), id2value[3]);
    builder->CreateBr(id2bb[10]);
    std::cout << "aft 50 calc vor diag" << std::endl;

// 69:                                               ; preds = %10
//   br label %70
    builder->SetInsertPoint(id2bb[69]);
    builder->CreateBr(id2bb[70]);

// 70:                                               ; preds = %69
//   %71 = load i32, i32* %1, align 4
//   %72 = add nsw i32 %71, 1
//   store i32 %72, i32* %1, align 4
//   br label %6

    builder->SetInsertPoint(id2bb[70]);
    id2value[71] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[72] = builder->CreateNSWAdd(id2value[71], llvm::ConstantInt::get(builder->getInt64Ty(), 1) );
    builder->CreateStore(id2value[72], id2value[1]);
    builder->CreateBr(id2bb[14]);

// 73:                                               ; preds = %6
//   ret void
    builder->SetInsertPoint(id2bb[73]);
    builder->CreateRetVoid();
}

void main_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    auto mainFunc = module->getFunction("LLVM_main");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", mainFunc);
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;
    builder->SetInsertPoint(entry);
    
    id2value[0] = mainFunc->getArg(0);
    id2value[1] = mainFunc->getArg(1);
    id2value[3] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[4] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[5] = builder->CreateAlloca(builder->getInt8PtrTy()->getPointerTo());

    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[3]);
    builder->CreateStore(id2value[0], id2value[4]);
    builder->CreateStore(id2value[1], id2value[5]);

    id2value[6] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[7] = builder->CreateLoad(builder->getInt8PtrTy()->getPointerTo(), id2value[5]);
    
    auto gl_initFunc = module->getFunction("gl_init");
    builder->CreateCall(gl_initFunc, {id2value[6], id2value[7]});
    auto reset_pictureFunc = module->getFunction("reset_picture");
    builder->CreateCall(reset_pictureFunc);
    auto loopFunc = module->getFunction("loop");
    builder->CreateCall(loopFunc);
    builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

}

void create_declarations(llvm::Module* module, llvm::IRBuilder<>* builder) {
    Point = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());
    pixels_type = llvm::ArrayType::get(llvm::ArrayType::get(Point, 800), 800);
    pixels_subtype= llvm::ArrayType::get(Point, 800);
    auto PPoint = llvm::PointerType::get(Point, 0);
    llvm::Constant* pixels = module->getOrInsertGlobal("pixels", pixels_type);
    module->getNamedGlobal("pixels")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("pixels")->setInitializer(module->getNamedGlobal("pixels")->getNullValue(pixels_type));
    module->getNamedGlobal("pixels")->setConstant(false);
    llvm::ArrayType* points_type = llvm::ArrayType::get(Point, 10);
    llvm::Constant* points = module->getOrInsertGlobal("points", points_type);
    module->getNamedGlobal("points")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("points")->setInitializer(module->getNamedGlobal("points")->getNullValue(points_type));
    module->getNamedGlobal("points")->setConstant(false);
    llvm::Constant* flag_no_recalc = module->getOrInsertGlobal("flag_no_recalc", builder->getInt1Ty());
    module->getNamedGlobal("flag_no_recalc")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("flag_no_recalc")->setInitializer(llvm::ConstantInt::get(builder->getInt1Ty(), 0));
    module->getNamedGlobal("flag_no_recalc")->setConstant(false);
    llvm::Constant* show_window = module->getOrInsertGlobal("show_window", builder->getInt1Ty());
    module->getNamedGlobal("show_window")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("show_window")->setInitializer(llvm::ConstantInt::get(builder->getInt1Ty(), 0));
    module->getNamedGlobal("show_window")->setConstant(false);
    //module->getOrInsertGlobal(Point);
    auto flag_no_recalc_check = module->getNamedGlobal("flag_no_recalc");
    if (flag_no_recalc_check == nullptr)
  {
    std::cout << "ALERT\n";
  }


    llvm::FunctionType *funcType = llvm::FunctionType::get(builder->getVoidTy(), false);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo()},false), llvm::Function::ExternalLinkage, "LLVM_main", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "reset_picture", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), {builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo()},false), llvm::Function::ExternalLinkage, "gl_init", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "display", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "timf", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "loop", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "int_rand", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "calc_vor_diag", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(), {PPoint, PPoint}, false), llvm::Function::ExternalLinkage, "dist", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "set_timer", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "calc_new_centers", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "gl_start", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), Point->getPointerTo(),false), llvm::Function::ExternalLinkage, "gl_put_pixel", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "gl_flush", module);
}

int main() {

    llvm::LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    llvm::Module *module = new llvm::Module("top", context);
    llvm::IRBuilder<> builder(context);
    create_declarations(module, &builder);
    // main_codegen(module, &builder);
    // reset_picture_codegen(module, &builder);
    // calc_vor_diag_codegen(module, &builder);
    dist_codegen(module, &builder);
    // calc_new_centers_codegen(module, &builder);
    // timf_codegen(module, &builder);
    // set_timer_codegen(module, &builder);
    // display_codegen(module, &builder);
    dump_codegen(module);
    return 0;

    //Interpreter of LLVM IR
//     llvm::ExecutionEngine *ee =
//         llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();

//           ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void *
//                                  {
//     if (fnName == "LLVM_main") {
//       return reinterpret_cast<void *>(LLVM_main);
//     }
//     return nullptr; });

//   ee->finalizeObject();
//   std::vector<llvm::GenericValue> noargs;
//   llvm::GenericValue v = ee->runFunction(mainFunc, noargs);


    return 0;
}