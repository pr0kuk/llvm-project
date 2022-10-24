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
/*
void display_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& displayFunc = module->getFunction("display");
    id2bb[1] = llvm::BasicBlock::Create(module->getContext(), "1", displayFunc );
    id2bb[4] = llvm::BasicBlock::Create(module->getContext(), "4", displayFunc );
    id2bb[11] = llvm::BasicBlock::Create(module->getContext(), "11", displayFunc );
    id2bb[14] = llvm::BasicBlock::Create(module->getContext(), "14", displayFunc );
    id2bb[18] = llvm::BasicBlock::Create(module->getContext(), "18", displayFunc );
    id2bb[31] = llvm::BasicBlock::Create(module->getContext(), "31", displayFunc );
    id2bb[33] = llvm::BasicBlock::Create(module->getContext(), "33", displayFunc );
    id2bb[39] = llvm::BasicBlock::Create(module->getContext(), "39", displayFunc );
    id2bb[40] = llvm::BasicBlock::Create(module->getContext(), "40", displayFunc );
    id2bb[42] = llvm::BasicBlock::Create(module->getContext(), "42", displayFunc );
    id2bb[43] = llvm::BasicBlock::Create(module->getContext(), "43", displayFunc );
    id2bb[46] = llvm::BasicBlock::Create(module->getContext(), "46", displayFunc );

    builder->CreateBr(id2bb[1]);

// 1:                                                ; preds = %11, %0
//   %2 = phi i64 [ 0, %0 ], [ %12, %11 ]
//   %3 = trunc i64 %2 to i32
//   br label %4
    builder->SetInsertPoint(id2bb[1]);
    auto&& phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[0]);
    phiNode->addIncoming(id2value[12], id2bb[11]);
    id2value[2] = phiNode;
    id2value[3] = builder->CreateTrunc(id2value[2], builder->getInt32Ty());
    builder->CreateBr(id2bb[4]);

// 4:                                                ; preds = %14, %1
//   %5 = phi i64 [ 0, %1 ], [ %16, %14 ]
//   %6 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 1
//   %7 = load i32, i32* %6, align 4, !tbaa !2
//   %8 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 2
//   %9 = load i32, i32* %8, align 4, !tbaa !7
//   %10 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 0
//   br label %18

    builder->SetInsertPoint(id2bb[4]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[1]);
    phiNode->addIncoming(id2value[16], id2bb[14]);
    id2value[5] = phiNode;

    auto&& pixels = module->getGlobalVariable("pixels");
    id2value[6] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[8] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[9] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[10] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 0)
        }
    );
    builder->CreateBr(id2bb[18]);



//     11:                                               ; preds = %14
//   %12 = add nuw nsw i64 %2, 1
//   %13 = icmp eq i64 %12, 800
//   br i1 %13, label %39, label %1


    builder->SetInsertPoint(id2bb[11]);
    id2value[12] = builder->CreateNSWAdd(id2value[2], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[13] = builder->CreateICmpEQ(id2value[12], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[13], id2bb[39], id2bb[1]);

// 14:                                               ; preds = %33
//   %15 = trunc i64 %5 to i32
//   store i32 %15, i32* %6, align 4, !tbaa !2
//   store i32 %3, i32* %8, align 4, !tbaa !7
//   %16 = add nuw nsw i64 %5, 1
//   %17 = icmp eq i64 %16, 800
//   br i1 %17, label %11, label %4

    builder->SetInsertPoint(id2bb[14]);
    id2value[15] = builder->CreateTrunc(id2value[5], builder->getInt32Ty());
    builder->CreateStore(id2value[15], id2value[6]);
    builder->CreateStore(id2value[3], id2value[8]);
    id2value[16] = builder->CreateNSWAdd(id2value[5], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[17] = builder->CreateICmpEQ(id2value[16], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[17], id2bb[11], id2bb[4]);



// 18:                                               ; preds = %33, %4
//   %19 = phi i64 [ 0, %4 ], [ %35, %33 ]
//   %20 = phi i32 [ 1000000000, %4 ], [ %34, %33 ]
//   %21 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 1
//   %22 = load i32, i32* %21, align 4, !tbaa !2
//   %23 = sub nsw i32 %22, %7
//   %24 = mul nsw i32 %23, %23
//   %25 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 2
//   %26 = load i32, i32* %25, align 4, !tbaa !7
//   %27 = sub nsw i32 %26, %9
//   %28 = mul nsw i32 %27, %27
//   %29 = add nuw nsw i32 %28, %24
//   %30 = icmp slt i32 %29, %20
//   br i1 %30, label %31, label %33


    builder->SetInsertPoint(id2bb[18]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[4]);
    phiNode->addIncoming(id2value[35], id2bb[33]);
    id2value[19] = phiNode;

    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 1000000000), id2bb[4]);
    phiNode->addIncoming(id2value[34], id2bb[33]);
    id2value[20] = phiNode;
    auto&& points = module->getGlobalVariable("points");
    id2value[21] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[21]);
    id2value[23] = builder->CreateNSWSub(id2value[22], id2value[7]);
    id2value[24] = builder->CreateNSWMul(id2value[23], id2value[23]);
    id2value[25] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[26] = builder->CreateLoad(builder->getInt32Ty(), id2value[25]);
    id2value[27] = builder->CreateNSWSub(id2value[26], id2value[9]);
    id2value[28] = builder->CreateNSWMul(id2value[27], id2value[27]);
    id2value[29] = builder->CreateNSWAdd(id2value[28], id2value[24]);
    id2value[30] = builder->CreateICmpSLT(id2value[29], id2value[20]);
    builder->CreateCondBr(id2value[30], id2bb[31], id2bb[33]);

// 31:                                               ; preds = %18
//   %32 = trunc i64 %19 to i32
//   store i32 %32, i32* %10, align 4, !tbaa !8
//   br label %33


    builder->SetInsertPoint(id2bb[31]);
    id2value[32] = builder->CreateTrunc(id2value[19], builder->getInt32Ty());
    builder->CreateStore(id2value[32], id2value[10]);
    builder->CreateBr(id2bb[33]);

// 33:                                               ; preds = %31, %18
//   %34 = phi i32 [ %29, %31 ], [ %20, %18 ]
//   %35 = add nuw nsw i64 %19, 1
//   %36 = icmp ult i64 %19, 9
//   %37 = icmp sgt i32 %34, 0
//   %38 = and i1 %36, %37
//   br i1 %38, label %18, label %14

    builder->SetInsertPoint(id2bb[33]);
    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(id2value[29], id2bb[31]);
    phiNode->addIncoming(id2value[20], id2bb[18]);
    id2value[34] = phiNode;
    id2value[35] = builder->CreateNSWAdd(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[36] = builder->CreateICmpULT(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 9));
    id2value[37] = builder->CreateICmpSGT(id2value[34], llvm::ConstantInt::get(builder->getInt64Ty(), 0));
    id2value[38] = builder->CreateAnd(id2value[36], id2value[37]);
        builder->CreateCondBr(id2value[38], id2bb[18], id2bb[14]);

// 39:                                               ; preds = %11
//   tail call void (...) @gl_start() #7
//   br label %40

    builder->SetInsertPoint(id2bb[39]);
    auto gl_startFunc = module->getFunction("gl_start");
    builder->CreateCall(gl_startFunc->getFunctionType(), gl_startFunc);
    builder->CreateBr(id2bb[40]);
// 40:                                               ; preds = %43, %39
//   %41 = phi i64 [ 0, %39 ], [ %44, %43 ]
//   br label %46

    builder->SetInsertPoint(id2bb[40]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[39]);
    phiNode->addIncoming(id2value[44], id2bb[43]);
    id2value[34] = phiNode;
    builder->CreateBr(id2bb[46]);

// 42:                                               ; preds = %43
//   tail call void (...) @gl_flush() #7
//   ret void

    builder->SetInsertPoint(id2bb[42]);
    auto gl_flushFunc = module->getFunction("gl_flush");
    builder->CreateCall(gl_flushFunc->getFunctionType(), gl_flushFunc);
    builder->CreateRetVoid();
// 43:                                               ; preds = %46
//   %44 = add nuw nsw i64 %41, 1
//   %45 = icmp eq i64 %44, 800
//   br i1 %45, label %42, label %40
    builder->SetInsertPoint(id2bb[43]);
    id2value[44] = builder->CreateNSWAdd(id2value[41], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[45] = builder->CreateICmpEQ(id2value[44], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[45], id2bb[42], id2bb[40]);
// 46:                                               ; preds = %46, %40
//   %47 = phi i64 [ 0, %40 ], [ %49, %46 ]
//   %48 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %41, i64 %47
//   tail call void @gl_put_pixel(%struct.Point* nonnull %48) #7
//   %49 = add nuw nsw i64 %47, 1
//   %50 = icmp eq i64 %49, 800
//   br i1 %50, label %43, label %46

 builder->SetInsertPoint(id2bb[46]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[40]);
    phiNode->addIncoming(id2value[49], id2bb[46]);
    id2value[47] = phiNode;

    pixels = module->getGlobalVariable("pixels");
    id2value[48] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[41],
            id2value[47],
        }
    );
    auto gl_put_pixelFunc = module->getFunction("gl_put_pixel");
    builder->CreateCall(gl_put_pixelFunc->getFunctionType(), gl_put_pixelFunc);
    id2value[49] = builder->CreateNSWAdd(id2value[47], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[50] = builder->CreateICmpEQ(id2value[49], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[50], id2bb[43], id2bb[46]);

}

void reset_picture_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& reset_pictureFunc = module->getFunction("reset_picture");
    id2bb[1] = llvm::BasicBlock::Create(module->getContext(), "1", reset_pictureFunc );
    id2bb[4] = llvm::BasicBlock::Create(module->getContext(), "4", reset_pictureFunc );
    id2bb[11] = llvm::BasicBlock::Create(module->getContext(), "11", reset_pictureFunc );
    id2bb[14] = llvm::BasicBlock::Create(module->getContext(), "14", reset_pictureFunc );
    id2bb[18] = llvm::BasicBlock::Create(module->getContext(), "18", reset_pictureFunc );
    id2bb[31] = llvm::BasicBlock::Create(module->getContext(), "31", reset_pictureFunc );
    id2bb[33] = llvm::BasicBlock::Create(module->getContext(), "33", reset_pictureFunc );
    id2bb[39] = llvm::BasicBlock::Create(module->getContext(), "39", reset_pictureFunc );
    id2bb[40] = llvm::BasicBlock::Create(module->getContext(), "40", reset_pictureFunc );

    //br label %40
    builder->CreateBr(id2bb[40]);


    // 1:                                                ; preds = %40, %11
    //   %2 = phi i64 [ %12, %11 ], [ 0, %40 ]
    //   %3 = trunc i64 %2 to i32
    //   br label %4
    builder->SetInsertPoint(id2bb[1]);
    auto&& phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(id2value[12], id2bb[11]);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[40]);
    id2value[2] = phiNode;
    id2value[3] = builder->CreateTrunc(id2value[2], builder->getInt32Ty());
    builder->CreateBr(id2bb[4]);
    std::cout << "aft reset_picture 1block" << std::endl;


// 4:                                                ; preds = %14, %1
//   %5 = phi i64 [ 0, %1 ], [ %16, %14 ]
//   %6 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 1
//   %7 = load i32, i32* %6, align 4, !tbaa !2
//   %8 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 2
//   %9 = load i32, i32* %8, align 4, !tbaa !7
//   %10 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 0
//   br label %18

    builder->SetInsertPoint(id2bb[4]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[1]);
    phiNode->addIncoming(id2value[0], id2bb[14]);
    id2value[5] = phiNode;

    auto&& pixels = module->getGlobalVariable("pixels");
    id2value[6] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[8] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[9] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[10] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 0)
        }
    );
    builder->CreateBr(id2bb[18]);

// 11:                                               ; preds = %14
//   %12 = add nuw nsw i64 %2, 1
//   %13 = icmp eq i64 %12, 800
//   br i1 %13, label %39, label %1

    builder->SetInsertPoint(id2bb[11]);
    id2value[12] = builder->CreateNSWAdd(id2value[2], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[13] = builder->CreateICmpEQ(id2value[12], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[13], id2bb[39], id2bb[1]);

// 14:                                               ; preds = %33
//   %15 = trunc i64 %5 to i32
//   store i32 %15, i32* %6, align 4, !tbaa !2
//   store i32 %3, i32* %8, align 4, !tbaa !7
//   %16 = add nuw nsw i64 %5, 1
//   %17 = icmp eq i64 %16, 800
//   br i1 %17, label %11, label %4


    builder->SetInsertPoint(id2bb[14]);
    id2value[15] = builder->CreateTrunc(id2value[5], builder->getInt32Ty());
    builder->CreateStore(id2value[15], id2value[6]);
    builder->CreateStore(id2value[3], id2value[8]);
    id2value[16] = builder->CreateNSWAdd(id2value[5], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[17] = builder->CreateICmpEQ(id2value[16], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[17], id2bb[11], id2bb[4]);

// 18:                                               ; preds = %33, %4
//   %19 = phi i64 [ 0, %4 ], [ %35, %33 ]
//   %20 = phi i32 [ 1000000000, %4 ], [ %34, %33 ]
//   %21 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 1
//   %22 = load i32, i32* %21, align 4, !tbaa !2
//   %23 = sub nsw i32 %22, %7
//   %24 = mul nsw i32 %23, %23
//   %25 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 2
//   %26 = load i32, i32* %25, align 4, !tbaa !7
//   %27 = sub nsw i32 %26, %9
//   %28 = mul nsw i32 %27, %27
//   %29 = add nuw nsw i32 %28, %24
//   %30 = icmp slt i32 %29, %20
//   br i1 %30, label %31, label %33

    builder->SetInsertPoint(id2bb[18]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[4]);
    phiNode->addIncoming(id2value[35], id2bb[33]);
    id2value[19] = phiNode;

    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 1000000000), id2bb[4]);
    phiNode->addIncoming(id2value[34], id2bb[33]);
    id2value[20] = phiNode;
    auto&& points = module->getGlobalVariable("points");
    id2value[21] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[21]);
    id2value[23] = builder->CreateNSWSub(id2value[22], id2value[7]);
    id2value[24] = builder->CreateNSWMul(id2value[23], id2value[23]);
    id2value[25] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[26] = builder->CreateLoad(builder->getInt32Ty(), id2value[25]);
    id2value[27] = builder->CreateNSWSub(id2value[26], id2value[9]);
    id2value[28] = builder->CreateNSWMul(id2value[27], id2value[27]);
    id2value[29] = builder->CreateNSWAdd(id2value[28], id2value[24]);
    id2value[30] = builder->CreateICmpSLT(id2value[29], id2value[20]);
    builder->CreateCondBr(id2value[30], id2bb[31], id2bb[33]);


// 31:                                               ; preds = %18
//   %32 = trunc i64 %19 to i32
//   store i32 %32, i32* %10, align 4, !tbaa !8
//   br label %33

    builder->SetInsertPoint(id2bb[31]);
    id2value[32] = builder->CreateTrunc(id2value[19], builder->getInt32Ty());
    builder->CreateStore(id2value[32], id2value[10]);
    builder->CreateBr(id2bb[33]);

// 33:                                               ; preds = %31, %18
//   %34 = phi i32 [ %29, %31 ], [ %20, %18 ]
//   %35 = add nuw nsw i64 %19, 1
//   %36 = icmp ult i64 %19, 9
//   %37 = icmp sgt i32 %34, 0
//   %38 = and i1 %36, %37
//   br i1 %38, label %18, label %14

    builder->SetInsertPoint(id2bb[33]);
    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(id2value[29], id2bb[31]);
    phiNode->addIncoming(id2value[20], id2bb[18]);
    id2value[34] = phiNode;
    id2value[35] = builder->CreateNSWAdd(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[36] = builder->CreateICmpULT(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 9));
    id2value[37] = builder->CreateICmpSGT(id2value[34], llvm::ConstantInt::get(builder->getInt64Ty(), 0));
    id2value[38] = builder->CreateAnd(id2value[36], id2value[37]);
        builder->CreateCondBr(id2value[38], id2bb[18], id2bb[14]);

// 39:                                               ; preds = %11
//   store i1 false, i1* @flag_no_recalc, align 4
//   ret void
    builder->SetInsertPoint(id2bb[39]);
    auto flag_no_recalc = module->getGlobalVariable("flag_no_recalc");
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), false), flag_no_recalc);

// 40:                                               ; preds = %40, %0
//   %41 = phi i64 [ 0, %0 ], [ %48, %40 ]
//   %42 = tail call i32 (...) @int_rand() #5
//   %43 = srem i32 %42, 800
//   %44 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %41, i32 1
//   store i32 %43, i32* %44, align 4, !tbaa !2
//   %45 = tail call i32 (...) @int_rand() #5
//   %46 = srem i32 %45, 800
//   %47 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %41, i32 2
//   store i32 %46, i32* %47, align 4, !tbaa !7
//   %48 = add nuw nsw i64 %41, 1
//   %49 = icmp eq i64 %48, 10
//   br i1 %49, label %1, label %40

    builder->SetInsertPoint(id2bb[40]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[0]);
    phiNode->addIncoming(id2bb[48], id2bb[40]);
    id2value[41] = phiNode;

    auto int_randFunc = module->getFunction("int_rand");
    id2value[42] = builder->CreateCall(
        int_randFunc->getFunctionType(),
        int_randFunc,
        {});
        id2value[43] = builder->CreateSRem(id2value[42], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    points = module->getGlobalVariable("points");
    id2value[44] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[41],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    builder->CreateStore(id2value[43], id2value[44]);


id2value[45] = builder->CreateCall(
        int_randFunc->getFunctionType(),
        int_randFunc,
        {});
        id2value[46] = builder->CreateSRem(id2value[45], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    id2value[47] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[41],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    builder->CreateStore(id2value[46], id2value[47]);
    id2value[48] = builder->CreateNSWAdd(id2value[41], llvm::ConstantInt::get(builder->getInt32Ty(), 1));
    id2value[49] = builder->CreateICmpEQ(id2value[48], llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    builder->CreateCondBr(id2value[49], id2bb[1], id2bb[40]);
}

void main_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    auto mainFunc = module->getFunction("LLVM_main");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", mainFunc);
    auto show_window = module->getGlobalVariable("show_window");

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;
    builder->SetInsertPoint(entry);

//   tail call void @gl_init(i32 %0, i8** %1) #7
//   tail call void @reset_picture()
//   tail call void @display() #7
//   %3 = load i1, i1* @show_window, align 4
//   br i1 %3, label %6, label %4
    std::cout << "bef all calls" << std::endl;
    //llvm::ArrayRef<llvm::Value*> Args = {id2value[0], id2value[1]};
    auto gl_initFunc = module->getFunction("gl_init");
    builder->CreateCall(gl_initFunc, {id2value[0], id2value[1]});

    auto reset_pictureFunc = module->getFunction("reset_picture");
    builder->CreateCall(reset_pictureFunc);
    
    auto displayFunc = module->getFunction("display");
    builder->CreateCall(displayFunc);
    std::cout << "aft all calls" << std::endl;

    id2bb[4] = llvm::BasicBlock::Create(module->getContext(), "4", mainFunc);
    id2bb[6] = llvm::BasicBlock::Create(module->getContext(), "6", mainFunc);
    std::cout << "aft labels" << std::endl;
    id2value[3] = builder->CreateLoad(builder->getInt1Ty(), show_window);
    builder->CreateCondBr(id2value[3], id2bb[6], id2bb[4]);
//     4:                                                ; preds = %2, %4
//   tail call void @timf(i32 10) #7
//   %5 = load i1, i1* @show_window, align 4
//   br i1 %5, label %6, label %4
    builder->SetInsertPoint(id2bb[4]);
    auto timfFunc = module->getFunction("timf");
    builder->CreateCall(timfFunc, llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    id2value[5] = builder->CreateLoad(builder->getInt1Ty(), show_window);
    std::cout << "aft 1block" << std::endl;


// 6:                                                ; preds = %4, %2
//   ret i32 0
    builder->SetInsertPoint(id2bb[6]);
    builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

}
*/

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
    auto&& points = module->getGlobalVariable("points");
    //id2value[10] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[15]});
    //id2value[11] = builder->CreateInBoundsGEP(Point, id2value[10], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)});
    builder->CreateStore(id2value[7], id2value[11]);
    id2value[12] = builder->CreateCall(int_randFunc);
    id2value[13] = builder->CreateSRem(id2value[12], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    id2value[14] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[15] = builder->CreateSExt(id2value[14], builder->getInt64Ty());
    //id2value[16] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[15]});
    //id2value[17] = builder->CreateInBoundsGEP(Point, id2value[16], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)});
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
    //builder->CreateCall(calc_vor_diagFunc, {});
    auto flag_no_recalc = module->getGlobalVariable("flag_no_recalc");
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 1), flag_no_recalc);
    builder->CreateRetVoid();
}

void dist_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;
    llvm::StructType* Point = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());

    auto&& distFunc = module->getFunction("dist");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", distFunc);
    builder->SetInsertPoint(entry);

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


    id2value[3] = builder->CreateAlloca(Point);
    id2value[4] = builder->CreateAlloca(Point);

    // builder->CreateStore(id2value[0], id2value[3]);
    // builder->CreateStore(id2value[1], id2value[4]);
    id2value[5] = builder->CreateLoad(Point, id2value[4]);
    //id2value[6] = builder->CreateInBoundsGEP(Point, id2value[5], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[8] = builder->CreateLoad(Point, id2value[3]);
    //id2value[9] = builder->CreateInBoundsGEP(Point, id2value[8], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );
    id2value[10] = builder->CreateLoad(builder->getInt32Ty(), id2value[9]);
    id2value[11] = builder->CreateNSWSub(id2value[7], id2value[10]);
    id2value[12] = builder->CreateLoad(Point, id2value[4]);
    //id2value[13] = builder->CreateInBoundsGEP(Point, id2value[12], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );
    id2value[14] = builder->CreateLoad(builder->getInt32Ty(), id2value[13]);
    id2value[15] = builder->CreateLoad(Point, id2value[3]);
    //id2value[13] = builder->CreateInBoundsGEP(Point, id2value[15], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 1)} );


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
    id2value[20] = builder->CreateLoad(Point, id2value[4]);
    //id2value[21] = builder->CreateInBoundsGEP(Point, id2value[20], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[21]);
    id2value[23] = builder->CreateLoad(Point, id2value[3]);
    //id2value[24] = builder->CreateInBoundsGEP(Point, id2value[23], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[25] = builder->CreateLoad(builder->getInt32Ty(), id2value[24]);
    id2value[26] = builder->CreateNSWSub(id2value[22], id2value[25]);
    id2value[27] = builder->CreateLoad(Point, id2value[4]);
    //id2value[28] = builder->CreateInBoundsGEP(Point, id2value[27], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
    id2value[29] = builder->CreateLoad(builder->getInt32Ty(), id2value[28]);
    id2value[30] = builder->CreateLoad(Point, id2value[3]);
    //id2value[31] = builder->CreateInBoundsGEP(Point, id2value[30], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) , llvm::ConstantInt::get(builder->getInt32Ty(), 2)} );
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

    id2bb[3] = llvm::BasicBlock::Create(module->getContext(), "3", displayFunc );
    id2bb[6] = llvm::BasicBlock::Create(module->getContext(), "6", displayFunc );
    id2bb[7] = llvm::BasicBlock::Create(module->getContext(), "7", displayFunc );
    id2bb[10] = llvm::BasicBlock::Create(module->getContext(), "10", displayFunc );
    id2bb[17] = llvm::BasicBlock::Create(module->getContext(), "17", displayFunc );
    id2bb[20] = llvm::BasicBlock::Create(module->getContext(), "20", displayFunc );
    id2bb[21] = llvm::BasicBlock::Create(module->getContext(), "21", displayFunc );
    id2bb[24] = llvm::BasicBlock::Create(module->getContext(), "24", displayFunc );

    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", displayFunc);
    builder->SetInsertPoint(entry);
//   %1 = alloca i32, align 4
//   %2 = alloca i32, align 4
//   call void @calc_vor_diag()
//   call void (...) @gl_start()
//   store i32 0, i32* %1, align 4
//   br label %3

// 3:                                                ; preds = %21, %0
//   %4 = load i32, i32* %1, align 4
//   %5 = icmp slt i32 %4, 800
//   br i1 %5, label %6, label %24

// 6:                                                ; preds = %3
//   store i32 0, i32* %2, align 4
//   br label %7

// 7:                                                ; preds = %17, %6
//   %8 = load i32, i32* %2, align 4
//   %9 = icmp slt i32 %8, 800
//   br i1 %9, label %10, label %20

// 10:                                               ; preds = %7
//   %11 = load i32, i32* %1, align 4
//   %12 = sext i32 %11 to i64
//   %13 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %12
//   %14 = load i32, i32* %2, align 4
//   %15 = sext i32 %14 to i64
//   %16 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %13, i64 0, i64 %15
//   call void @gl_put_pixel(%struct.Point* %16)
//   br label %17

// 17:                                               ; preds = %10
//   %18 = load i32, i32* %2, align 4
//   %19 = add nsw i32 %18, 1
//   store i32 %19, i32* %2, align 4
//   br label %7

// 20:                                               ; preds = %7
//   br label %21

// 21:                                               ; preds = %20
//   %22 = load i32, i32* %1, align 4
//   %23 = add nsw i32 %22, 1
//   store i32 %23, i32* %1, align 4
//   br label %3

// 24:                                               ; preds = %3
//   call void (...) @gl_flush()
//   ret void

    builder->CreateRetVoid();
}

void set_timer_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& set_timerFunc = module->getFunction("set_timer");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", set_timerFunc);
    builder->SetInsertPoint(entry);

//   %2 = alloca i32, align 4
//   store i32 %0, i32* %2, align 4
//   ret void

    id2value[2] = builder->CreateAlloca(builder->getInt32Ty());
    //builder->CreateStore(id2value[0], id2value[2]);
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
    auto&& pixels = module->getGlobalVariable("pixels");
    auto&& points = module->getGlobalVariable("points");

    //id2value[25] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[24]});
    id2value[26] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[27] = builder->CreateSExt(id2value[26], builder->getInt64Ty());
    //id2value[28] = builder->CreateInBoundsGEP(pixels[0]->getValueType(), id2value[25], {llvm::ConstantInt::get(builder->getInt32Ty(),0), id2value[27]});
    id2value[29] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[30] = builder->CreateSExt(id2value[29], builder->getInt64Ty());
    //id2value[31] = builder->CreateInBoundsGEP(points->getValueType(), points, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[30]});
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
    //id2value[40] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[39]});
    id2value[41] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[42] = builder->CreateSExt(id2value[41], builder->getInt64Ty());
    //id2value[28] = builder->CreateInBoundsGEP(pixels[0]->getValueType(), id2value[40], {llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[42]});
    //id2value[44] = builder->CreateInBoundsGEP(Point, id2value[43], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) ,llvm::ConstantInt::get(builder->getInt32Ty(), 0)  });
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
    //id2value[54] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[53]});
    id2value[55] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[56] = builder->CreateSExt(id2value[55], builder->getInt64Ty());
    //id2value[57] = builder->CreateInBoundsGEP(pixels[0]->getValueType(), id2value[54], {llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[56]});
    //id2value[58] = builder->CreateInBoundsGEP(Point, id2value[57], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) ,llvm::ConstantInt::get(builder->getInt32Ty(), 1)  });
    builder->CreateStore(id2value[51], id2value[58]);

    id2value[59] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[60] = builder->CreateLoad(builder->getInt32Ty(), id2value[1]);
    id2value[61] = builder->CreateSExt(id2value[60], builder->getInt64Ty());
    //id2value[62] = builder->CreateInBoundsGEP(pixels->getValueType(), pixels, {llvm::ConstantInt::get(builder->getInt64Ty(), 0) , id2value[62]});
    id2value[63] = builder->CreateLoad(builder->getInt32Ty(), id2value[2]);
    id2value[64] = builder->CreateSExt(id2value[63], builder->getInt64Ty());

    //id2value[65] = builder->CreateInBoundsGEP(pixels[0]->getValueType(), id2value[62], {llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[64]});
    //id2value[66] = builder->CreateInBoundsGEP(Point, id2value[65], {llvm::ConstantInt::get(builder->getInt32Ty(), 0) ,llvm::ConstantInt::get(builder->getInt32Ty(), 2)  });
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
    std::cout << "aft entrypoint" << std::endl;
    id2value[3] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[4] = builder->CreateAlloca(builder->getInt32Ty());
    id2value[5] = builder->CreateAlloca(builder->getInt8PtrTy()->getPointerTo());
    std::cout << "aft alloca" << std::endl;

    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), 0), id2value[3]);
    std::cout << "aft 1store" << std::endl;
    //builder->CreateStore(id2value[0], id2value[4]);
    std::cout << "aft 2store" << std::endl;
    //builder->CreateStore(id2value[1], id2value[5]);
    std::cout << "aft 3store" << std::endl;

    id2value[6] = builder->CreateLoad(builder->getInt32Ty(), id2value[4]);
    id2value[7] = builder->CreateLoad(builder->getInt8PtrTy()->getPointerTo(), id2value[5]);
    std::cout << "aft load" << std::endl;
    
    auto gl_initFunc = module->getFunction("gl_init");
    builder->CreateCall(gl_initFunc, {id2value[6], id2value[7]});
    auto reset_pictureFunc = module->getFunction("reset_picture");
    builder->CreateCall(reset_pictureFunc);
    auto loopFunc = module->getFunction("loop");
    builder->CreateCall(loopFunc);
    builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

}


void create_declarations(llvm::Module* module, llvm::IRBuilder<>* builder) {
    // declare void @main()
    llvm::FunctionType *funcType = 
        llvm::FunctionType::get(builder->getVoidTy(), false);
    llvm::StructType* Point = llvm::StructType::get(builder->getInt32Ty(), builder->getInt32Ty(),builder->getInt32Ty());

    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo()},false), llvm::Function::ExternalLinkage, "LLVM_main", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "reset_picture", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), {builder->getInt32Ty(), builder->getInt8PtrTy()->getPointerTo()},false), llvm::Function::ExternalLinkage, "gl_init", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "display", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "timf", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "loop", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "int_rand", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "calc_vor_diag", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(), {Point, Point}, false), llvm::Function::ExternalLinkage, "dist", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "set_timer", module);
    llvm::Function::Create(llvm::FunctionType::get(builder->getInt32Ty(),false), llvm::Function::ExternalLinkage, "calc_new_centers", module);

}

int main() {

    llvm::LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    llvm::Module *module = new llvm::Module("top", context);
    llvm::IRBuilder<> builder(context);
    llvm::StructType* Point = llvm::StructType::get(builder.getInt32Ty(), builder.getInt32Ty(),builder.getInt32Ty());
    llvm::ArrayType* pixels_type = llvm::ArrayType::get(llvm::ArrayType::get(Point, 800), 800);
    llvm::Constant* pixels = module->getOrInsertGlobal("pixels", pixels_type);
    module->getNamedGlobal("pixels")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("pixels")->setInitializer(module->getNamedGlobal("pixels")->getNullValue(pixels_type));
    llvm::ArrayType* points_type = llvm::ArrayType::get(Point, 10);
    llvm::Constant* points = module->getOrInsertGlobal("points", points_type);
    module->getNamedGlobal("points")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("points")->setInitializer(module->getNamedGlobal("points")->getNullValue(points_type));
    llvm::Constant* flag_no_recalc = module->getOrInsertGlobal("flag_no_recalc", builder.getInt1Ty());
    module->getNamedGlobal("flag_no_recalc")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("flag_no_recalc")->setInitializer(llvm::ConstantInt::get(builder.getInt1Ty(), 0));
    llvm::Constant* show_window = module->getOrInsertGlobal("show_window", builder.getInt1Ty());
    module->getNamedGlobal("show_window")->setLinkage(llvm::GlobalVariable::InternalLinkage);
    module->getNamedGlobal("show_window")->setInitializer(llvm::ConstantInt::get(builder.getInt1Ty(), 0));
    create_declarations(module, &builder);
    main_codegen(module, &builder);
    reset_picture_codegen(module, &builder);
    calc_vor_diag_codegen(module, &builder);
    dist_codegen(module, &builder);
    display_codegen(module, &builder);
    // calc_new_centers_codegen(module, &builder);
    // calc_timf_codegen(module, &builder);
    set_timer_codegen(module, &builder);
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