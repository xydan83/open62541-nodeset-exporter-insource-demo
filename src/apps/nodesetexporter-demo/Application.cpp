//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright 2025 (c) Aleksander Rozhkov <aleksprog@hotmail.com>
//

#include "apps/nodesetexporter-demo/Application.h"
#include "apps/nodesetexporter-demo/BrowseOperations.h"


#include <Encoder_types.h>
#include <Statuses.h>
#include <UATypesContainer.h>

#include <open62541/client.h>
#include <open62541/client_config_default.h>

#include <iostream>

namespace apps::nodesetexporter::demo
{
using ::nodesetexporter::open62541::UATypesContainer;
using StatusResults = ::nodesetexporter::common::statuses::StatusResults<>;
using LogLevel = ::nodesetexporter::common::LogLevel;
using EncoderTypes = ::nodesetexporter::common::EncoderTypes;
using ::nodesetexporter::ExportNodesetFromClient;

void Application::StartExport()
{
    // The first main operation is collecting units for export. Can take a long time.
    std::cout << "Browse node lists for export" << std::endl;
    std::map<std::string, std::vector<UATypesContainer<UA_ExpandedNodeId>>> node_ids_export;

    // If we can have many starting nodes
    for (const auto& start_node_id_s : m_start_node_ids)
    {
        // Use special C++ wrapper (UATypesContainer) for UA objects
        std::vector<UATypesContainer<UA_ExpandedNodeId>> export_node_id_list;
        UATypesContainer<UA_ExpandedNodeId> start_node_id(UA_EXPANDEDNODEID(start_node_id_s.data()), UA_TYPES_EXPANDEDNODEID);
        // Browse nodes from start node
        auto client_result = browseoperations::GrabChildNodeIdsFromStartNodeId(m_client, start_node_id, export_node_id_list);
        std::cout << "Browsing operation from starting NodeID " << start_node_id_s << std::endl;
        if (client_result == StatusResults::Fail)
        {
            throw std::runtime_error("Browsing error: " + std::string(UA_StatusCode_name(client_result.GetReserveCode())));
        }

        node_ids_export.emplace(start_node_id_s, std::move(export_node_id_list));
    }

    // The second main operation is export. Nodesetexporter library function. Can take a long time.
    std::cout << "Launch export" << std::endl;
    auto nodeexporter_status = ExportNodesetFromClient(*m_client, node_ids_export, std::move(m_export_filename), std::nullopt, m_opt);
    if (nodeexporter_status != StatusResults::Good)
    {
        throw std::runtime_error("Export error");
    }
}

int Application::Run()
{
    try
    {
        UA_StatusCode client_result = UA_STATUSCODE_GOOD;

        // Preparing auxiliary export options
        m_opt.internal_log_level = LogLevel::Info;
        m_opt.encoder_types = EncoderTypes::XML;

        m_client = UA_Client_new();
        std::cout << "Configuration the Open62541 Client" << std::endl;
        auto* cli_config = UA_Client_getConfig(m_client);
        UA_ClientConfig_setDefault(cli_config);

        std::cout << "Connecting a Client to a Server" << std::endl;
        client_result = UA_Client_connect(m_client, m_client_endpointUrl.data());

        if (!UA_StatusCode_isGood(client_result))
        {
            std::cout << "OPC UA Client error: " << UA_StatusCode_name(client_result) << std::endl;
            return EXIT_FAILURE;
        }

        StartExport();

        std::cout << "I`m leaving..." << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

} // namespace apps::nodesetexporter::demo