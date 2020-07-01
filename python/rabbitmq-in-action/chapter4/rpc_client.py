#env python3

import time, json, pika

def reply_callback(channel, method, header, body):
    """Receives RPC Server replies."""
    print("RPC Reply --- %s" % body)
    channel.stop_consuming()

if __name__ == "__main__":
    creds_broker = pika.PlainCredentials("rpc_user", "rpcme")
    conn_params = pika.ConnectionParameters("localhost",
                                            virtual_host = "/",
                                            credentials = creds_broker)

    conn_broker = pika.BlockingConnection(conn_params)
    channel = conn_broker.channel()

    msg = json.dumps({
        "client_name": "RPC Client 1.0",
        "time": time.time()
        })

    #empty string for queue, the broker will create a unique queue name
    result = channel.queue_declare(queue="", exclusive = True, auto_delete = True)
    msg_props = pika.BasicProperties()
    msg_props.reply_to = result.method.queue
    channel.basic_publish(body = msg,
                          exchange = "rpc",
                          properties = msg_props,
                          routing_key = "ping")

    print("Sent 'ping' RPC call. Waiting for reply...")

    channel.basic_consume(result.method.queue,
                          on_message_callback = reply_callback,
                          consumer_tag = result.method.queue)
    channel.start_consuming()
