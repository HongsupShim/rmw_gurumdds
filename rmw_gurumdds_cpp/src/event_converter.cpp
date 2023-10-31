// Copyright 2019 GurumNetworks, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <utility>

#include "rmw_gurumdds_cpp/event_converter.hpp"



/// mapping of RMW_EVENT to the corresponding dds_StatusKind.
static const dds_StatusKind g_mask_map[]{
    dds_LIVELINESS_CHANGED_STATUS,         // RMW_EVENT_LIVELINESS_CHANGED
    dds_REQUESTED_DEADLINE_MISSED_STATUS,  // RMW_EVENT_REQUESTED_DEADLINE_MISSED
    dds_REQUESTED_INCOMPATIBLE_QOS_STATUS, // RMW_EVENT_REQUESTED_QOS_INCOMPATIBLE
    dds_SAMPLE_LOST_STATUS,                // RMW_EVENT_MESSAGE_LOST
    dds_INCONSISTENT_TOPIC_STATUS,
    dds_SUBSCRIPTION_MATCHED_STATUS,
    // dds_SUBSCRIPTION_INCOMAPATIBLE_TYPE,
    // dds_SUBSCRIPTION_MATCHED_STATUS,
    dds_LIVELINESS_LOST_STATUS,          // RMW_EVENT_LIVELINESS_LOST
    dds_OFFERED_DEADLINE_MISSED_STATUS,  // RMW_EVENT_OFFERED_DEADLINE_MISSED
    dds_OFFERED_INCOMPATIBLE_QOS_STATUS, // RMW_EVENT_OFFERED_QOS_INCOMPATIBLE
    dds_INCONSISTENT_TOPIC_STATUS,
    dds_PUBLICATION_MATCHED_STATUS
    // dds_PUBLISHER_INCOMPATIBLE_TYPE,
    // dds_PUBLICATION_MATCHED_STATUS,
};

// RMW_EVENT_SUBSCRIPTION_INCOMPATIBLE_TYPE,
//  RMW_EVENT_SUBSCRIPTION_MATCHED,


  
//  RMW_EVENT_PUBLISHER_INCOMPATIBLE_TYPE,
//  RMW_EVENT_PUBLICATION_MATCHED,


// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_INCONSISTENT_TOPIC_STATUS;			// 0x0001 << 0
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_OFFERED_DEADLINE_MISSED_STATUS;		// 0x0001 << 1
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_REQUESTED_DEADLINE_MISSED_STATUS;		// 0x0001 << 2
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_OFFERED_INCOMPATIBLE_QOS_STATUS;		// 0x0001 << 5
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_REQUESTED_INCOMPATIBLE_QOS_STATUS;	// 0x0001 << 6
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_SAMPLE_LOST_STATUS;					// 0x0001 << 7
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_SAMPLE_REJECTED_STATUS;				// 0x0001 << 8
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_DATA_ON_READERS_STATUS;				// 0x0001 << 9
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_DATA_AVAILABLE_STATUS;				// 0x0001 << 10
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_LIVELINESS_LOST_STATUS;				// 0x0001 << 11
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_LIVELINESS_CHANGED_STATUS;			// 0x0001 << 12
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_PUBLICATION_MATCHED_STATUS;	 		// 0x0001 << 13
// GURUMDDS_C_DLLAPI extern const dds_StatusKind dds_SUBSCRIPTION_MATCHED_STATUS;			// 0x0001 << 14

dds_StatusKind get_status_kind_from_rmw(const rmw_event_type_t event_t)
{
  if (!is_event_supported(event_t))
  {
    return 0;
  }

  return g_mask_map[static_cast<int>(event_t)];
}

bool is_event_supported(const rmw_event_type_t event_t)
{
  return 0 <= event_t && event_t < RMW_EVENT_INVALID;
}

rmw_ret_t check_dds_ret_code(const dds_ReturnCode_t dds_return_code)
{
  if (dds_return_code == dds_RETCODE_OK)
  {
    return RMW_RET_OK;
  }
  else if (dds_return_code == dds_RETCODE_ERROR)
  {
    return RMW_RET_ERROR;
  }
  else if (dds_return_code == dds_RETCODE_TIMEOUT)
  {
    return RMW_RET_TIMEOUT;
  }
  else
  {
    return RMW_RET_ERROR;
  }
}
