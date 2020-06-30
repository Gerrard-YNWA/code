#env pyhton3

import json, pika

def critical_notify(channel, method, header, body):
    print("critical notify callback: message %s" % (str(json.loads(body))))
    channel.basic_ack(delivery_tag = method.delivery_tag)

def rate_limit_notify(channel, method, header, body):
    print("rate limit notify callback: message %s" % (str(json.loads(body))))
    channel.basic_ack(delivery_tag = method.delivery_tag)

if __name__ == "__main__":
    AMQP_SERVER = "localhost"
    AMQP_USER = "alert_user"
    AMQP_PASS = "alertme"
    AMQP_VHOST = "/"
    AMQP_EXCHANGE = "alerts"

    creds_broker = pika.PlainCredentials(AMQP_USER, AMQP_PASS)
    conn_params = pika.ConnectionParameters(AMQP_SERVER, virtual_host = AMQP_VHOST, credentials = creds_broker)

    conn_broker = pika.BlockingConnection(conn_params)
    channel = conn_broker.channel()

    channel.exchange_declare(exchange = AMQP_EXCHANGE, exchange_type = "topic", auto_delete = False)

    channel.queue_declare(queue = "critical", auto_delete = False)
    channel.queue_bind(queue = "critical", exchange = AMQP_EXCHANGE, routing_key = "critical.*")

    channel.queue_declare(queue = "rate_limit", auto_delete = False)
    channel.queue_bind(queue = "rate_limit", exchange = AMQP_EXCHANGE, routing_key = "*.rate_limit")

    channel.basic_consume(queue = "critical", on_message_callback = critical_notify, auto_ack = False, consumer_tag = "critical")
    channel.basic_consume(queue = "rate_limit", on_message_callback = rate_limit_notify, auto_ack = False, consumer_tag = "rate_limit")
    
    print("Ready for alerts!")

    channel.start_consuming()
