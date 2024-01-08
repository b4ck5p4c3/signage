import mqtt from "mqtt";
import fs from "fs";
import dotenv from "dotenv";
import { Protocol, convertToCp1251, EffectType, Direction, Position } from "./signage/protocol";

dotenv.config();

const CA_CERTIFICATE_PATH = process.env.CA_CERTIFICATE_PATH ?? 'ca-cert.pem';
const MQTT_URL = process.env.MQTT_URL ?? 'mqtts://b4ck:b4ck@mqtt.internal.0x08.in';

const client = mqtt.connect(MQTT_URL, {
    ca: [ fs.readFileSync(CA_CERTIFICATE_PATH) ]
});

client.on('connect', () => {
    console.info('Connected to mqtt');

    const protocol = new Protocol();
    
    client.publish('bus/devices/openspace-signage/message', Buffer.from(protocol.serializeSetMessage({
        message: {
            data: convertToCp1251("Test message, тестовое сообщение"),
            brightness: 4,
            effectType: EffectType.SCROLL,
            scrollEffect: {
                direction: Direction.RIGHT_TO_LEFT,
                speed: 50
            }
        },
        duration: 20000,
        priority: 1
    })), () => {
        client.end();
    });
});
client.on('error', e => {
    console.error(`Error: ${e}`);
});