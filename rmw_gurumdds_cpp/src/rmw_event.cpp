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

#include "rmw/rmw.h"
#include "rmw/error_handling.h"
#include "rmw/impl/cpp/macros.hpp"

#include "rmw_gurumdds_cpp/event_converter.hpp"
#include "rmw_gurumdds_cpp/identifier.hpp"
#include "rmw_gurumdds_cpp/types.hpp"

static rmw_ret_t
init_rmw_event(
    const char *identifier,
    rmw_event_t *rmw_event,
    const char *topic_endpoint_impl_identifier,
    void *data,
    rmw_event_type_t event_type)
{
  RMW_CHECK_ARGUMENT_FOR_NULL(identifier, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(rmw_event, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(topic_endpoint_impl_identifier, RMW_RET_INVALID_ARGUMENT);
  RMW_CHECK_ARGUMENT_FOR_NULL(data, RMW_RET_INVALID_ARGUMENT);

  RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
      topic endpoint,
      topic_endpoint_impl_identifier,
      identifier,
      return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

  rmw_event->implementation_identifier = topic_endpoint_impl_identifier;
  rmw_event->data = data;
  rmw_event->event_type = event_type;

  return RMW_RET_OK;
}

extern "C"
{
  rmw_ret_t
  rmw_publisher_event_init(
      rmw_event_t *rmw_event,
      const rmw_publisher_t *publisher,
      rmw_event_type_t event_type)
  {
    return init_rmw_event(
        RMW_GURUMDDS_ID,
        rmw_event,
        publisher->implementation_identifier,
        publisher->data,
        event_type);
  }

  rmw_ret_t
  rmw_subscription_event_init(
      rmw_event_t *rmw_event,
      const rmw_subscription_t *subscription,
      rmw_event_type_t event_type)
  {
    return init_rmw_event(
        RMW_GURUMDDS_ID,
        rmw_event,
        subscription->implementation_identifier,
        subscription->data,
        event_type);
  }

  void update_matched(int32_t total_count,
                      int32_t total_count_change,
                      int32_t current_count,
                      int32_t current_count_change)
  {
  }

  rmw_ret_t
  rmw_take_event(
      const rmw_event_t *event_handle,
      void *event_info,
      bool *taken)
  {
    RMW_CHECK_ARGUMENT_FOR_NULL(event_handle, RMW_RET_INVALID_ARGUMENT);
    RMW_CHECK_ARGUMENT_FOR_NULL(event_info, RMW_RET_INVALID_ARGUMENT);
    RMW_CHECK_ARGUMENT_FOR_NULL(taken, RMW_RET_INVALID_ARGUMENT);

    RMW_CHECK_TYPE_IDENTIFIERS_MATCH(
        event handle,
        event_handle->implementation_identifier,
        RMW_GURUMDDS_ID,
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION);

    rmw_ret_t ret_code = RMW_RET_UNSUPPORTED;

    if (is_event_supported(event_handle->event_type))
    {
      *taken = (ret_code == RMW_RET_OK);
      return ret_code;
    }
  }

  rmw_ret_t
  rmw_event_set_callback(
      rmw_event_t *rmw_event,
      rmw_event_callback_t callback,
      const void *user_data)
  {
    (void)rmw_event;
    (void)callback;
    (void)user_data;

    RMW_SET_ERROR_MSG("rmw_event_set_callback not implemented");
    return RMW_RET_UNSUPPORTED;
  }

} // extern "C"

void on_sub_matched(_dds_DataReader *self, const dds_SubscriptionMatchedStatus *status)
{
  dds_SubscriptionMatchedStatus set_status;
  auto ret = dds_DataReader_get_subscription_matched_status(self, &set_status);
}

void on_pub_matched(const _dds_DataWriter *self, const dds_PublicationMatchedStatus *status)
{
  dds_PublicationMatchedStatus set_status;
  auto ret = dds_DataWriter_get_publication_matched_status((_dds_DataWriter*)self, &set_status);
}