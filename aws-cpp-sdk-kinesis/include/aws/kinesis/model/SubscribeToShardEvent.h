﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/kinesis/Kinesis_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/kinesis/model/Record.h>
#include <aws/kinesis/model/ChildShard.h>
#include <utility>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
  class JsonView;
} // namespace Json
} // namespace Utils
namespace Kinesis
{
namespace Model
{

  /**
   * <p>After you call <a>SubscribeToShard</a>, Kinesis Data Streams sends events of
   * this type over an HTTP/2 connection to your consumer.</p><p><h3>See Also:</h3>  
   * <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/kinesis-2013-12-02/SubscribeToShardEvent">AWS
   * API Reference</a></p>
   */
  class AWS_KINESIS_API SubscribeToShardEvent
  {
  public:
    SubscribeToShardEvent();
    SubscribeToShardEvent(Aws::Utils::Json::JsonView jsonValue);
    SubscribeToShardEvent& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p/>
     */
    inline const Aws::Vector<Record>& GetRecords() const{ return m_records; }

    /**
     * <p/>
     */
    inline bool RecordsHasBeenSet() const { return m_recordsHasBeenSet; }

    /**
     * <p/>
     */
    inline void SetRecords(const Aws::Vector<Record>& value) { m_recordsHasBeenSet = true; m_records = value; }

    /**
     * <p/>
     */
    inline void SetRecords(Aws::Vector<Record>&& value) { m_recordsHasBeenSet = true; m_records = std::move(value); }

    /**
     * <p/>
     */
    inline SubscribeToShardEvent& WithRecords(const Aws::Vector<Record>& value) { SetRecords(value); return *this;}

    /**
     * <p/>
     */
    inline SubscribeToShardEvent& WithRecords(Aws::Vector<Record>&& value) { SetRecords(std::move(value)); return *this;}

    /**
     * <p/>
     */
    inline SubscribeToShardEvent& AddRecords(const Record& value) { m_recordsHasBeenSet = true; m_records.push_back(value); return *this; }

    /**
     * <p/>
     */
    inline SubscribeToShardEvent& AddRecords(Record&& value) { m_recordsHasBeenSet = true; m_records.push_back(std::move(value)); return *this; }


    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline const Aws::String& GetContinuationSequenceNumber() const{ return m_continuationSequenceNumber; }

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline bool ContinuationSequenceNumberHasBeenSet() const { return m_continuationSequenceNumberHasBeenSet; }

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline void SetContinuationSequenceNumber(const Aws::String& value) { m_continuationSequenceNumberHasBeenSet = true; m_continuationSequenceNumber = value; }

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline void SetContinuationSequenceNumber(Aws::String&& value) { m_continuationSequenceNumberHasBeenSet = true; m_continuationSequenceNumber = std::move(value); }

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline void SetContinuationSequenceNumber(const char* value) { m_continuationSequenceNumberHasBeenSet = true; m_continuationSequenceNumber.assign(value); }

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline SubscribeToShardEvent& WithContinuationSequenceNumber(const Aws::String& value) { SetContinuationSequenceNumber(value); return *this;}

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline SubscribeToShardEvent& WithContinuationSequenceNumber(Aws::String&& value) { SetContinuationSequenceNumber(std::move(value)); return *this;}

    /**
     * <p>Use this as <code>SequenceNumber</code> in the next call to
     * <a>SubscribeToShard</a>, with <code>StartingPosition</code> set to
     * <code>AT_SEQUENCE_NUMBER</code> or <code>AFTER_SEQUENCE_NUMBER</code>. Use
     * <code>ContinuationSequenceNumber</code> for checkpointing because it captures
     * your shard progress even when no data is written to the shard.</p>
     */
    inline SubscribeToShardEvent& WithContinuationSequenceNumber(const char* value) { SetContinuationSequenceNumber(value); return *this;}


    /**
     * <p>The number of milliseconds the read records are from the tip of the stream,
     * indicating how far behind current time the consumer is. A value of zero
     * indicates that record processing is caught up, and there are no new records to
     * process at this moment.</p>
     */
    inline long long GetMillisBehindLatest() const{ return m_millisBehindLatest; }

    /**
     * <p>The number of milliseconds the read records are from the tip of the stream,
     * indicating how far behind current time the consumer is. A value of zero
     * indicates that record processing is caught up, and there are no new records to
     * process at this moment.</p>
     */
    inline bool MillisBehindLatestHasBeenSet() const { return m_millisBehindLatestHasBeenSet; }

    /**
     * <p>The number of milliseconds the read records are from the tip of the stream,
     * indicating how far behind current time the consumer is. A value of zero
     * indicates that record processing is caught up, and there are no new records to
     * process at this moment.</p>
     */
    inline void SetMillisBehindLatest(long long value) { m_millisBehindLatestHasBeenSet = true; m_millisBehindLatest = value; }

    /**
     * <p>The number of milliseconds the read records are from the tip of the stream,
     * indicating how far behind current time the consumer is. A value of zero
     * indicates that record processing is caught up, and there are no new records to
     * process at this moment.</p>
     */
    inline SubscribeToShardEvent& WithMillisBehindLatest(long long value) { SetMillisBehindLatest(value); return *this;}


    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline const Aws::Vector<ChildShard>& GetChildShards() const{ return m_childShards; }

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline bool ChildShardsHasBeenSet() const { return m_childShardsHasBeenSet; }

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline void SetChildShards(const Aws::Vector<ChildShard>& value) { m_childShardsHasBeenSet = true; m_childShards = value; }

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline void SetChildShards(Aws::Vector<ChildShard>&& value) { m_childShardsHasBeenSet = true; m_childShards = std::move(value); }

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline SubscribeToShardEvent& WithChildShards(const Aws::Vector<ChildShard>& value) { SetChildShards(value); return *this;}

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline SubscribeToShardEvent& WithChildShards(Aws::Vector<ChildShard>&& value) { SetChildShards(std::move(value)); return *this;}

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline SubscribeToShardEvent& AddChildShards(const ChildShard& value) { m_childShardsHasBeenSet = true; m_childShards.push_back(value); return *this; }

    /**
     * <p>The list of the child shards of the current shard, returned only at the end
     * of the current shard.</p>
     */
    inline SubscribeToShardEvent& AddChildShards(ChildShard&& value) { m_childShardsHasBeenSet = true; m_childShards.push_back(std::move(value)); return *this; }

  private:

    Aws::Vector<Record> m_records;
    bool m_recordsHasBeenSet = false;

    Aws::String m_continuationSequenceNumber;
    bool m_continuationSequenceNumberHasBeenSet = false;

    long long m_millisBehindLatest;
    bool m_millisBehindLatestHasBeenSet = false;

    Aws::Vector<ChildShard> m_childShards;
    bool m_childShardsHasBeenSet = false;
  };

} // namespace Model
} // namespace Kinesis
} // namespace Aws
