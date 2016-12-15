/* -------------------------------------------------------------------------- *
 * Copyright (c) 2010-2016 C. Pizzolato, M. Reggiani                          *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License");            *
 * you may not use this file except in compliance with the License.           *
 * You may obtain a copy of the License at:                                   *
 * http://www.apache.org/licenses/LICENSE-2.0                                 *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

#ifndef rtosim_QueueToInverseKinematicsOsens_h
#define rtosim_QueueToInverseKinematicsOsens_h

#include <string>
#include <memory>
#include <Simbody.h>

#include "rtosim/ThreadPoolJobs.h"
#include "rtosim/JobsCreatorOsens.h"
#include "rtosim/IKSequencer.h"
#include "rtosim/IKSolverParallelOsens.h"
#include "rtosim/concurrency/Queue.h"
#include "rtosim/concurrency/Latch.h"
#include "rtosim/queue/MarkerSetQueue.h"
#include "rtosim/queue/GeneralisedCoordinatesQueue.h"
#include "rtosim/StopWatch.h"

namespace rtosim {

    class QueueToInverseKinematicsOsens {
    public:
        QueueToInverseKinematicsOsens(
            OrientationSetQueue& inputOrientationSetQueue,
            rtosim::GeneralisedCoordinatesQueue& outputGeneralisedCoordinateQueue,
            rtosim::Concurrency::Latch& doneWithSubscriptions,
            rtosim::Concurrency::Latch& doneWithExecution,
            const std::string& osimModelFilename,
            unsigned nThreads,
            double solverAccuracy = 1e-9,
            double constraintWeight = SimTK::Infinity);

        QueueToInverseKinematicsOsens(
            OrientationSetQueue& inputOrientationSetQueue,
            rtosim::GeneralisedCoordinatesQueue& outputGeneralisedCoordinateQueue,
            rtosim::Concurrency::Latch& doneWithSubscriptions,
            rtosim::Concurrency::Latch& doneWithExecution,
            const std::string& osimModelFilename,
            unsigned nThreads,
            const std::string& ikTaskSetFilename,
            double solverAccuracy = 1e-9,
            double constraintWeight = SimTK::Infinity);
        void operator()();

        std::vector < StopWatch > getProcessingTimes() { return stopWatch_; }
    private:
        OrientationSetQueue& inputOrientationSetQueue_;
        rtosim::GeneralisedCoordinatesQueue& outputGeneralisedCoordinateQueue_;
        rtosim::Concurrency::Latch& doneWithSubscriptions_;
        rtosim::Concurrency::Latch& doneWithExecution_;
        unsigned nThreads_;
        std::string osimModelFilename_;
        std::string ikTaskSetFilename_;
        bool useIkTaskSet_;
        double solverAccuracy_;
        double constraintWeight_;
        std::vector < StopWatch > stopWatch_;
    };
}

#endif