/*
 * S2E Selective Symbolic Execution Framework
 *
 * Copyright (c) 2010, Dependable Systems Laboratory, EPFL
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Dependable Systems Laboratory, EPFL nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE DEPENDABLE SYSTEMS LABORATORY, EPFL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Vitaly Chipounov, Volodymyr Kuznetsov
 *
 */

#ifndef S2ETOOLS_TBTRACE_H
#define S2ETOOLS_TBTRACE_H

#include <lib/ExecutionTracer/LogParser.h>
#include <lib/ExecutionTracer/ModuleParser.h>

#include <ostream>
#include <fstream>

#include <lib/BinaryReaders/Library.h>

namespace s2etools
{

class TbTrace
{
public:

private:
    LogEvents *m_events;
    ModuleCache *m_cache;
    Library *m_library;
    std::ofstream &m_output;

    sigc::connection m_connection;

    bool m_hasItems;
    bool m_hasModuleInfo;
    bool m_hasDebugInfo;

    void onItem(unsigned traceIndex,
                const s2e::plugins::ExecutionTraceItemHeader &hdr,
                void *item);

    void printDebugInfo(uint64_t pid, uint64_t pc);
    void printRegisters(const s2e::plugins::ExecutionTraceTb *te);
public:
    TbTrace(Library *lib, ModuleCache *cache, LogEvents *events, std::ofstream &ofs);
    virtual ~TbTrace();

    void outputTraces(const std::string &Path) const;
    bool hasItems() const {
        return m_hasItems;
    }

    bool hasModuleInfo() const {
        return m_hasModuleInfo;
    }

    bool hasDebugInfo() const {
        return m_hasDebugInfo;
    }

};

class TbTraceTool
{
private:
    LogParser m_parser;

    Library m_binaries;

public:
    TbTraceTool();
    ~TbTraceTool();

    void process();
    void flatTrace();
};


}

#endif