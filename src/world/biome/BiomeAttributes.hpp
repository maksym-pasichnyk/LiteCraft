#pragma once

struct BiomeAttributes {
    float temperature;
    float humidity;
    float altitude;
    float weirdness;
    float offset;

    float getAttributeDifference(const BiomeAttributes& attributes) const {
        return (temperature - attributes.temperature) * (temperature - attributes.temperature)
               + (humidity - attributes.humidity) * (humidity - attributes.humidity)
               + (altitude - attributes.altitude) * (altitude - attributes.altitude)
               + (weirdness - attributes.weirdness) * (weirdness - attributes.weirdness)
               + (offset - attributes.offset) * (offset - attributes.offset);
    }
};