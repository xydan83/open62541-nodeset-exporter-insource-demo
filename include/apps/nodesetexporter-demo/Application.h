//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright 2025 (c) Aleksander Rozhkov <aleksprog@hotmail.com>
//

#ifndef APPS_NODESETEXPORTERDEMO_APPLICATION_H
#define APPS_NODESETEXPORTERDEMO_APPLICATION_H


#include <LoggerBase.h>
#include <NodesetExporter.h>

#include <span>

namespace apps::nodesetexporter::demo
{

class InterruptException : public std::runtime_error
{
public:
    InterruptException() = delete;
    explicit InterruptException(const std::string& arg)
        : runtime_error(arg)
    {
    }
};

class Application
{

public:
    Application() = delete;

    explicit Application(std::span<const char*> args)
        : m_args(args)
        , m_client(nullptr)
        , m_client_endpointUrl(m_args[1])
    {
        m_start_node_ids.emplace_back(std::string(m_args[2]));
    }

    ~Application()
    {
        if (m_client != nullptr)
        {
            UA_Client_delete(m_client);
        }
    }

    /**
     * @brief Start export operation
     */
    void StartExport();

    /**
     * @brief Initialization and startup process.
     * @return EXIT_SUCCESS in case of normal shutdown or EXIT_FAILURE.
     */
    int Run();

private:
    std::span<const char*> const m_args{};

    UA_Client* m_client;

    std::string m_export_filename = "demo_export.xml";
    std::string m_client_endpointUrl{};
    std::vector<std::string> m_start_node_ids{};
    ::nodesetexporter::Options m_opt{};
};

} // namespace apps::nodesetexporter::demo


#endif // APPS_NODESETEXPORTERDEMO_APPLICATION_H