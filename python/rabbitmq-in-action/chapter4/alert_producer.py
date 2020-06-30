#env python3

from optparse import  OptionParser
import json, pika

if __name__ == '__main__':
    opt_parser = OptionParser()
    opt_parser.add_option("-r",
                          "--routing-key",
                          dest = "routing_key",
                          help = "Routing key for message" + \
                                  "(e.g. myalert.im)")

    opt_parser.add_option("-m",
                          "--message",
                          dest= "message",
                          help = "Message text for alert.")

    args = opt_parser.parse_args()[0]

    creds_broker = pika.PlainCredentials("alert_user", "alertme")
    conn_params = pika.ConnectionParameters("localhost",
                                            virtual_host = "/",
                                            credentials = creds_broker)

    conn_broker = pika.BlockingConnection(conn_params)
    channel = conn_broker.channel()

    msg = json.dumps(args.message)
    msg_props = pika.BasicProperties()
    msg_props.content_type = "application/json"

    channel.basic_publish(exchange = "alerts",
                          routing_key = args.routing_key,
                          body = msg,
                          properties = msg_props)

    print("Sent message %s tagged with routing key '%s' to exchange '/'." % (json.dumps(args.message), args.routing_key))
