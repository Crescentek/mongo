/**
 *    Copyright (C) 2024-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once
#include "mongo/db/query/plan_explainer.h"

namespace mongo {

class PlanExplainerExpress final : public PlanExplainer {
public:
    PlanExplainerExpress(const mongo::CommonStats* stats, bool isClusteredOnId)
        : _stats(stats), _isClusteredOnId(isClusteredOnId) {}

    const ExplainVersion& getVersion() const override {
        static const ExplainVersion kExplainVersion = "1";
        return kExplainVersion;
    }

    bool isMultiPlan() const override {
        return false;
    }

    std::string getPlanSummary() const override {
        return "EXPRESS";
    }

    void getSummaryStats(PlanSummaryStats* statsOut) const override;

    PlanStatsDetails getWinningPlanStats(ExplainOptions::Verbosity verbosity) const override;

    PlanStatsDetails getWinningPlanTrialStats() const override {
        return {};
    }

    std::vector<PlanStatsDetails> getRejectedPlansStats(
        ExplainOptions::Verbosity verbosity) const override {
        return {};
    }

    BSONObj getOptimizerDebugInfo() const {
        return {};
    }

    bool isClusteredOnId() const {
        return _isClusteredOnId;
    }

private:
    const mongo::CommonStats* _stats;
    bool _isClusteredOnId;
};

}  // namespace mongo
