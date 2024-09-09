/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include "role_determination.hpp"
#include "services.hpp"

#include <sdbusplus/async.hpp>
#include <xyz/openbmc_project/State/BMC/Redundancy/server.hpp>

namespace rbmc
{

using RedundancyIntf =
    sdbusplus::xyz::openbmc_project::State::BMC::server::Redundancy;
using RedundancyInterface = sdbusplus::server::object_t<RedundancyIntf>;

/**
 * @class Manager
 *
 * Manages the high level operations of the redundant
 * BMC functionality.
 */
class Manager
{
  public:
    Manager() = delete;
    ~Manager() = default;
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&&) = delete;

    /**
     * @brief Constructor
     *
     * @param[in] ctx - The async context object
     * @param[in] services - The services object to interface with system data.
     */
    Manager(sdbusplus::async::context& ctx,
            std::unique_ptr<Services>&& services);

  private:
    /**
     * @brief Kicks off the Manager startup
     */
    sdbusplus::async::task<> startup();

    /**
     * @brief Emits a heartbeat signal every second
     *
     * The sibling gets this via the sibling app to
     * know all's well.
     */
    sdbusplus::async::task<> doHeartBeat();

    /**
     * @brief Determines the BMC role
     *
     * @return Role - The role
     */
    Role determineRole();

    /**
     * @brief The async context object
     */
    sdbusplus::async::context& ctx;

    /**
     * @brief The Redundancy D-Bus interface
     */
    RedundancyInterface redundancyInterface;

    /**
     * @brief The services object
     *
     * Wraps system interfaces.
     */
    std::unique_ptr<Services> services;
};

} // namespace rbmc
