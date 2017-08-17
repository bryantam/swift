//===--- WALAWaler.h - frontend utility methods ------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file contains declarations of utility methods for parsing and
// performing semantic on modules.
//
//===----------------------------------------------------------------------===//

#include "swift/SIL/SILModule.h"

#ifndef SWIFT_WALAWALKER_H
#define SWIFT_WALAWALKER_H

//TODO: do this after silgen
//and possibly the "mandatory optimization pipeline"

namespace swift {

    class WALAWalker {
    private:
    	void printInstrDebugLocInfo(raw_ostream &outstream, SILInstruction &instr, SourceManager &srcMgr);
    	void printInstrMemoryReleasingInfo(raw_ostream &outstream, SILInstruction &instr);
    	void printInstrOpInfo(raw_ostream &outstream, SILInstruction &instr);
    	void printInstrValueKindINfo(raw_ostream &outstream, SILInstruction &instr);
    	void printSILInstrInfo(raw_ostream &outstream, SILInstruction &instr, SourceManager &srcMgr);
    public:
        void foo();        
        void print(SILModule &SM);
    };

}

#endif
