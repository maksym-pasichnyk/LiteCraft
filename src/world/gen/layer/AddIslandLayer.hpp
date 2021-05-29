#pragma once

#include "traits/IBishopTransformer.hpp"
#include "LayerUtil.hpp"

#include <memory>

struct AddIslandLayer : IBishopTransformer<AddIslandLayer> {
    int apply(INoiseRandom& context, int d0, int d1, int d2, int d3, int d4) {
        if (!LayerUtil::isShallowOcean(d4) || LayerUtil::isShallowOcean(d3) && LayerUtil::isShallowOcean(d2) && LayerUtil::isShallowOcean(d0) && LayerUtil::isShallowOcean(d1)) {
            if (!LayerUtil::isShallowOcean(d4) && (LayerUtil::isShallowOcean(d3) || LayerUtil::isShallowOcean(d0) || LayerUtil::isShallowOcean(d2) || LayerUtil::isShallowOcean(d1)) &&  context.nextInt(5) == 0) {
                if (LayerUtil::isShallowOcean(d3)) {
                    return d4 == 4 ? 4 : d3;
                }

                if (LayerUtil::isShallowOcean(d0)) {
                    return d4 == 4 ? 4 : d0;
                }

                if (LayerUtil::isShallowOcean(d2)) {
                    return d4 == 4 ? 4 : d2;
                }

                if (LayerUtil::isShallowOcean(d1)) {
                    return d4 == 4 ? 4 : d1;
                }
            }

            return d4;
        }

        int i = 1;
        int j = 1;

        if (!LayerUtil::isShallowOcean(d3) && context.nextInt(i++) == 0) {
            j = d3;
        }

        if (!LayerUtil::isShallowOcean(d2) && context.nextInt(i++) == 0) {
            j = d2;
        }

        if (!LayerUtil::isShallowOcean(d0) && context.nextInt(i++) == 0) {
            j = d0;
        }

        if (!LayerUtil::isShallowOcean(d1) && context.nextInt(i++) == 0) {
            j = d1;
        }

        if (context.nextInt(3) == 0) {
            return j;
        }

        return j == 4 ? 4 : d4;
    }
};