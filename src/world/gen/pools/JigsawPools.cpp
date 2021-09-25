#include "JigsawPools.hpp"

#include <map>
#include <fstream>
#include <filesystem>
#include <configs.hpp>
#include <fmt/format.h>
#include <json/json.hpp>
#include <range/v3/all.hpp>
#include <world/gen/feature/ConfiguredFeatures.hpp>
#include <world/gen/feature/jigsaw/JigsawPattern.hpp>
#include <world/gen/feature/jigsaw/ListJigsawPiece.hpp>
#include <world/gen/feature/jigsaw/EmptyJigsawPiece.hpp>
#include <world/gen/feature/jigsaw/SingleJigsawPiece.hpp>
#include <world/gen/feature/jigsaw/FeatureJigsawPiece.hpp>
#include <world/gen/feature/jigsaw/LegacySingleJigsawPiece.hpp>
#include <world/gen/feature/processor/ProcessorLists.hpp>

Registry<JigsawPattern> JigsawPools::pools;

static auto create(const std::string& location, const std::string& fallback, const std::vector<std::pair<JigsawPiece::Factory, int>>& factories, JigsawProjection placement) -> JigsawPattern* {
	std::vector<JigsawPiece *> pool;
	std::vector<std::pair<std::unique_ptr<JigsawPiece>, int>> elements;

	for (auto&& [factory, count] : factories) {
		auto element = factory(placement);
		for (int i = 0; i < count; ++i) {
			pool.emplace_back(element.get());
		}
		elements.emplace_back(std::move(element), count);
	}

    return JigsawPools::pools.add(location, std::make_unique<JigsawPattern>(JigsawPattern{
        .location = location,
        .fallback = fallback,
        .pool = std::move(pool),
        .elements = std::move(elements)
    }));
}

void JigsawPools::init() {
//    PlainVillagePools::init();
//    SnowyVillagePools::init();
//    SavannaVillagePools::init();
//    DesertVillagePools::init();
//    TaigaVillagePools::init();
//    PillagerOutpostPools::init();
//    BastionRemnantsPieces::init();

    for (auto&& entry : std::filesystem::directory_iterator{"definitions/pools"}) {
        if (!entry.is_regular_file()) {
            continue;
        }

        auto o = Json::Read::read(std::ifstream{entry.path(), std::ios::binary}).value();

        auto elements = o.at("elements").to_array() | ranges::views::transform([](const auto& element) -> std::pair<std::unique_ptr<JigsawPiece>, int> {
            return std::pair{
                JigsawPiece::from_json(element.at("element")),
                static_cast<int>(element.at("weight"))
            };
        }) | ranges::to_vector;

        std::vector<JigsawPiece *> pool{};
        for (auto&& [element, count] : elements) {
            for (int i = 0; i < count; ++i) {
                pool.emplace_back(element.get());
            }
        }

        JigsawPools::pools.add(o.at("name").to_string(), std::make_unique<JigsawPattern>(JigsawPattern{
            .location = o.at("name").to_string(),
            .fallback = o.at("fallback").to_string(),
            .pool = std::move(pool),
            .elements = std::move(elements)
        }));
    }

//    for (auto&& [name, pool] : JigsawPools::pools.objects) {
//        const auto path = std::filesystem::path(fmt::format("definitions/pools/{}.json", name));
//
//        std::filesystem::create_directories(path.parent_path());
//
//        auto elements = pool->elements | ranges::views::transform([](const std::pair<JigsawPiece*, int>& element) -> Json {
//            return Json{ {"element", element.first->to_json()}, {"weight", element.second} };
//        }) | ranges::to_vector;
//
//        std::ofstream out{path, std::ios::binary};
//        out << Json{
//            {"name", pool->location},
//            {"fallback", pool->fallback},
//            {"elements", std::move(elements)}
//        };
//    }
}

void PlainVillagePools::init() {
	create(
		"village/plains/town_centers",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/town_centers/plains_fountain_01", ProcessorLists::MOSSIFY_20_PERCENT), 50 },
			{JigsawPiece::legacy("village/plains/town_centers/plains_meeting_point_1", ProcessorLists::MOSSIFY_20_PERCENT), 50 },
			{JigsawPiece::legacy("village/plains/town_centers/plains_meeting_point_2"), 50 },
			{JigsawPiece::legacy("village/plains/town_centers/plains_meeting_point_3", ProcessorLists::MOSSIFY_70_PERCENT), 50 },
			{JigsawPiece::legacy("village/plains/zombie/town_centers/plains_fountain_01", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/zombie/town_centers/plains_meeting_point_1", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/zombie/town_centers/plains_meeting_point_2", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/zombie/town_centers/plains_meeting_point_3", ProcessorLists::ZOMBIE_PLAINS), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/streets",
		"village/plains/terminators",
		{
			{JigsawPiece::legacy("village/plains/streets/corner_01", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/corner_02", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/corner_03", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/straight_01", ProcessorLists::STREET_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/streets/straight_02", ProcessorLists::STREET_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/streets/straight_03", ProcessorLists::STREET_PLAINS), 7 },
			{JigsawPiece::legacy("village/plains/streets/straight_04", ProcessorLists::STREET_PLAINS), 7 },
			{JigsawPiece::legacy("village/plains/streets/straight_05", ProcessorLists::STREET_PLAINS), 3 },
			{JigsawPiece::legacy("village/plains/streets/straight_06", ProcessorLists::STREET_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/streets/crossroad_01", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/crossroad_02", ProcessorLists::STREET_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/streets/crossroad_03", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/crossroad_04", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/crossroad_05", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/crossroad_06", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/streets/turn_01", ProcessorLists::STREET_PLAINS), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/plains/zombie/streets",
		"village/plains/terminators",
		{
			{JigsawPiece::legacy("village/plains/zombie/streets/corner_01", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/corner_02", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/corner_03", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/straight_01", ProcessorLists::STREET_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/zombie/streets/straight_02", ProcessorLists::STREET_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/zombie/streets/straight_03", ProcessorLists::STREET_PLAINS), 7 },
			{JigsawPiece::legacy("village/plains/zombie/streets/straight_04", ProcessorLists::STREET_PLAINS), 7 },
			{JigsawPiece::legacy("village/plains/zombie/streets/straight_05", ProcessorLists::STREET_PLAINS), 3 },
			{JigsawPiece::legacy("village/plains/zombie/streets/straight_06", ProcessorLists::STREET_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/zombie/streets/crossroad_01", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/crossroad_02", ProcessorLists::STREET_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/zombie/streets/crossroad_03", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/crossroad_04", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/crossroad_05", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/crossroad_06", ProcessorLists::STREET_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/streets/turn_01", ProcessorLists::STREET_PLAINS), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/plains/houses",
		"village/plains/terminators",
		{
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_2", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_3", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_4", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_5", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_6", ProcessorLists::MOSSIFY_10_PERCENT), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_7", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_house_8", ProcessorLists::MOSSIFY_10_PERCENT), 3 },
			{JigsawPiece::legacy("village/plains/houses/plains_medium_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_medium_house_2", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_big_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_butcher_shop_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_butcher_shop_2", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_tool_smith_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_fletcher_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_shepherds_house_1"), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_armorer_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_fisher_cottage_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_tannery_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_cartographer_1", ProcessorLists::MOSSIFY_10_PERCENT), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_library_1", ProcessorLists::MOSSIFY_10_PERCENT), 5 },
			{JigsawPiece::legacy("village/plains/houses/plains_library_2", ProcessorLists::MOSSIFY_10_PERCENT), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_masons_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_weaponsmith_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_temple_3", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_temple_4", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_stable_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_stable_2"), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_large_farm_1", ProcessorLists::FARM_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_farm_1", ProcessorLists::FARM_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/houses/plains_animal_pen_1"), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_animal_pen_2"), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_animal_pen_3"), 5 },
			{JigsawPiece::legacy("village/plains/houses/plains_accessory_1"), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_meeting_point_4", ProcessorLists::MOSSIFY_70_PERCENT), 3 },
			{JigsawPiece::legacy("village/plains/houses/plains_meeting_point_5"), 1 },
			{JigsawPiece::empty(), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/zombie/houses",
		"village/plains/terminators",
		{
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_2", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_3", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_4", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_5", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_6", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_7", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_small_house_8", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_medium_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_medium_house_2", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_big_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_butcher_shop_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_butcher_shop_2", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_tool_smith_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_fletcher_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_shepherds_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_armorer_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_fisher_cottage_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_tannery_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_cartographer_1", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_library_1", ProcessorLists::ZOMBIE_PLAINS), 3 },
			{JigsawPiece::legacy("village/plains/houses/plains_library_2", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_masons_house_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_weaponsmith_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_temple_3", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_temple_4", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_stable_1", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_stable_2", ProcessorLists::ZOMBIE_PLAINS), 2 },
			{JigsawPiece::legacy("village/plains/houses/plains_large_farm_1", ProcessorLists::ZOMBIE_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/houses/plains_small_farm_1", ProcessorLists::ZOMBIE_PLAINS), 4 },
			{JigsawPiece::legacy("village/plains/houses/plains_animal_pen_1", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/houses/plains_animal_pen_2", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_animal_pen_3", ProcessorLists::ZOMBIE_PLAINS), 5 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_meeting_point_4", ProcessorLists::ZOMBIE_PLAINS), 3 },
			{JigsawPiece::legacy("village/plains/zombie/houses/plains_meeting_point_5", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::empty(), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/terminators",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/terminators/terminator_01", ProcessorLists::STREET_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_02", ProcessorLists::STREET_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_03", ProcessorLists::STREET_PLAINS), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_04", ProcessorLists::STREET_PLAINS), 1 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/plains/trees",
		"empty",
		{
			{JigsawPiece::feature(ConfiguredFeatures::OAK), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/plains_lamp_1"), 2 },
			{JigsawPiece::feature(ConfiguredFeatures::OAK), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::FLOWER_PLAIN), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_HAY), 1 },
			{JigsawPiece::empty(), 2 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/zombie/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/plains_lamp_1", ProcessorLists::ZOMBIE_PLAINS), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::OAK), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::FLOWER_PLAIN), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_HAY), 1 },
			{JigsawPiece::empty(), 2 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/plains/villagers/baby"), 1 },
			{JigsawPiece::legacy("village/plains/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/plains/zombie/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/zombie/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/plains/zombie/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/common/animals",
		"empty",
		{
			{JigsawPiece::legacy("village/common/animals/cows_1"), 7 },
			{JigsawPiece::legacy("village/common/animals/pigs_1"), 7 },
			{JigsawPiece::legacy("village/common/animals/horses_1"), 1 },
			{JigsawPiece::legacy("village/common/animals/horses_2"), 1 },
			{JigsawPiece::legacy("village/common/animals/horses_3"), 1 },
			{JigsawPiece::legacy("village/common/animals/horses_4"), 1 },
			{JigsawPiece::legacy("village/common/animals/horses_5"), 1 },
			{JigsawPiece::legacy("village/common/animals/sheep_1"), 1 },
			{JigsawPiece::legacy("village/common/animals/sheep_2"), 1 },
			{JigsawPiece::empty(), 5 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/common/sheep",
		"empty",
		{
			{JigsawPiece::legacy("village/common/animals/sheep_1"), 1 },
			{JigsawPiece::legacy("village/common/animals/sheep_2"), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/common/cats",
		"empty",
		{
			{JigsawPiece::legacy("village/common/animals/cat_black"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_british"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_calico"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_persian"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_ragdoll"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_red"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_siamese"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_tabby"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_white"), 1 },
			{JigsawPiece::legacy("village/common/animals/cat_jellie"), 1 },
			{JigsawPiece::empty(), 3 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/common/butcher_animals",
		"empty",
		{
			{JigsawPiece::legacy("village/common/animals/cows_1"), 3 },
			{JigsawPiece::legacy("village/common/animals/pigs_1"), 3 },
			{JigsawPiece::legacy("village/common/animals/sheep_1"), 1 },
			{JigsawPiece::legacy("village/common/animals/sheep_2"), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/common/iron_golem",
		"empty",
		{
			{JigsawPiece::legacy("village/common/iron_golem"), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/common/well_bottoms",
		"empty",
		{
			{JigsawPiece::legacy("village/common/well_bottom"), 1 }
		},
		JigsawProjection::RIGID
	);

}

void SnowyVillagePools::init() {
	create(
		"village/snowy/town_centers",
		"empty",
		{
			{JigsawPiece::legacy("village/snowy/town_centers/snowy_meeting_point_1"), 100 },
			{JigsawPiece::legacy("village/snowy/town_centers/snowy_meeting_point_2"), 50 },
			{JigsawPiece::legacy("village/snowy/town_centers/snowy_meeting_point_3"), 150 },
			{JigsawPiece::legacy("village/snowy/zombie/town_centers/snowy_meeting_point_1"), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/town_centers/snowy_meeting_point_2"), 1 },
			{JigsawPiece::legacy("village/snowy/zombie/town_centers/snowy_meeting_point_3"), 3 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/streets",
		"village/snowy/terminators",
		{
			{JigsawPiece::legacy("village/snowy/streets/corner_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/corner_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/corner_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/square_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/straight_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/streets/straight_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/streets/straight_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/streets/straight_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 7 },
			{JigsawPiece::legacy("village/snowy/streets/straight_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/streets/straight_08", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/streets/crossroad_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 },
			{JigsawPiece::legacy("village/snowy/streets/crossroad_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/crossroad_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/crossroad_05", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/crossroad_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/streets/turn_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/snowy/zombie/streets",
		"village/snowy/terminators",
		{
			{JigsawPiece::legacy("village/snowy/zombie/streets/corner_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/corner_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/corner_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/square_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/straight_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/straight_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/straight_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/straight_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 7 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/straight_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/straight_08", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/crossroad_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/crossroad_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/crossroad_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/crossroad_05", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/crossroad_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/streets/turn_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/snowy/houses",
		"village/snowy/terminators",
		{
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_2"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_3"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_4"), 3 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_5"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_6"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_7"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_small_house_8"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_medium_house_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_medium_house_2"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_medium_house_3"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_butchers_shop_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_butchers_shop_2"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_tool_smith_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_fletcher_house_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_shepherds_house_1"), 3 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_armorer_house_1"), 1 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_armorer_house_2"), 1 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_fisher_cottage"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_tannery_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_cartographer_house_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_library_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_masons_house_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_masons_house_2"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_weapon_smith_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_temple_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_farm_1", ProcessorLists::FARM_SNOWY), 3 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_farm_2", ProcessorLists::FARM_SNOWY), 3 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_animal_pen_1"), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_animal_pen_2"), 2 },
			{JigsawPiece::empty(), 6 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/zombie/houses",
		"village/snowy/terminators",
		{
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_2", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_3", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_4", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_5", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_6", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_7", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_small_house_8", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_medium_house_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_medium_house_2", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/zombie/houses/snowy_medium_house_3", ProcessorLists::ZOMBIE_SNOWY), 1 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_butchers_shop_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_butchers_shop_2", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_tool_smith_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_fletcher_house_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_shepherds_house_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_armorer_house_1", ProcessorLists::ZOMBIE_SNOWY), 1 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_armorer_house_2", ProcessorLists::ZOMBIE_SNOWY), 1 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_fisher_cottage", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_tannery_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_cartographer_house_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_library_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_masons_house_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_masons_house_2", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_weapon_smith_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_temple_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_farm_1", ProcessorLists::ZOMBIE_SNOWY), 3 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_farm_2", ProcessorLists::ZOMBIE_SNOWY), 3 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_animal_pen_1", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::legacy("village/snowy/houses/snowy_animal_pen_2", ProcessorLists::ZOMBIE_SNOWY), 2 },
			{JigsawPiece::empty(), 6 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/terminators",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/terminators/terminator_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/snowy/trees",
		"empty",
		{
			 { JigsawPiece::feature(ConfiguredFeatures::SPRUCE), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/snowy/snowy_lamp_post_01"), 4 },
			{JigsawPiece::legacy("village/snowy/snowy_lamp_post_02"), 4 },
			{JigsawPiece::legacy("village/snowy/snowy_lamp_post_03"), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::SPRUCE), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_SNOW), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_ICE), 1 },
			{JigsawPiece::empty(), 9 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/zombie/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/snowy/snowy_lamp_post_01", ProcessorLists::ZOMBIE_SNOWY), 1 },
			{JigsawPiece::legacy("village/snowy/snowy_lamp_post_02", ProcessorLists::ZOMBIE_SNOWY), 1 },
			{JigsawPiece::legacy("village/snowy/snowy_lamp_post_03", ProcessorLists::ZOMBIE_SNOWY), 1 },
			{JigsawPiece::feature(ConfiguredFeatures::SPRUCE), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_SNOW), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_ICE), 4 },
			{JigsawPiece::empty(), 7 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/snowy/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/snowy/villagers/baby"), 1 },
			{JigsawPiece::legacy("village/snowy/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/snowy/zombie/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/snowy/zombie/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/snowy/zombie/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);
}

void SavannaVillagePools::init() {
	create(
		"village/savanna/town_centers",
		"empty",
		{
			{JigsawPiece::legacy("village/savanna/town_centers/savanna_meeting_point_1"), 100 },
			{JigsawPiece::legacy("village/savanna/town_centers/savanna_meeting_point_2"), 50 },
			{JigsawPiece::legacy("village/savanna/town_centers/savanna_meeting_point_3"), 150 },
			{JigsawPiece::legacy("village/savanna/town_centers/savanna_meeting_point_4"), 150 },
			{JigsawPiece::legacy("village/savanna/zombie/town_centers/savanna_meeting_point_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/town_centers/savanna_meeting_point_2", ProcessorLists::ZOMBIE_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/zombie/town_centers/savanna_meeting_point_3", ProcessorLists::ZOMBIE_SAVANNA), 3 },
			{JigsawPiece::legacy("village/savanna/zombie/town_centers/savanna_meeting_point_4", ProcessorLists::ZOMBIE_SAVANNA), 3 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/streets",
		"village/savanna/terminators",
		{
			{JigsawPiece::legacy("village/savanna/streets/corner_01", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/corner_03", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/straight_02", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/streets/straight_04", ProcessorLists::STREET_SAVANNA), 7 },
			{JigsawPiece::legacy("village/savanna/streets/straight_05", ProcessorLists::STREET_SAVANNA), 3 },
			{JigsawPiece::legacy("village/savanna/streets/straight_06", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/streets/straight_08", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/streets/straight_09", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/streets/straight_10", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/streets/straight_11", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/streets/crossroad_02", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/streets/crossroad_03", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/crossroad_04", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/crossroad_05", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/crossroad_06", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/crossroad_07", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/split_01", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/split_02", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/streets/turn_01", ProcessorLists::STREET_SAVANNA), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/savanna/zombie/streets",
		"village/savanna/zombie/terminators",
		{
			{JigsawPiece::legacy("village/savanna/zombie/streets/corner_01", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/corner_03", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_02", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_04", ProcessorLists::STREET_SAVANNA), 7 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_05", ProcessorLists::STREET_SAVANNA), 3 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_06", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_08", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_09", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_10", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/straight_11", ProcessorLists::STREET_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/crossroad_02", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/crossroad_03", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/crossroad_04", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/crossroad_05", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/crossroad_06", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/crossroad_07", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/split_01", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/split_02", ProcessorLists::STREET_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/streets/turn_01", ProcessorLists::STREET_SAVANNA), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/savanna/houses",
		"village/savanna/terminators",
		{
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_2"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_3"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_4"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_5"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_6"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_7"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_house_8"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_medium_house_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_medium_house_2"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_butchers_shop_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_butchers_shop_2"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_tool_smith_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_fletcher_house_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_shepherd_1"), 7 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_armorer_1"), 1 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_fisher_cottage_1"), 3 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_tannery_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_cartographer_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_library_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_mason_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_weaponsmith_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_weaponsmith_2"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_temple_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_temple_2"), 3 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_large_farm_1", ProcessorLists::FARM_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_large_farm_2", ProcessorLists::FARM_SAVANNA), 6 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_farm", ProcessorLists::FARM_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_animal_pen_1"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_animal_pen_2"), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_animal_pen_3"), 2 },
			{JigsawPiece::empty(), 5 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/zombie/houses",
		"village/savanna/zombie/terminators",
		{
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_2", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_3", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_4", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_5", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_6", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_7", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_small_house_8", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_medium_house_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_medium_house_2", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_butchers_shop_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_butchers_shop_2", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_tool_smith_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_fletcher_house_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_shepherd_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_armorer_1", ProcessorLists::ZOMBIE_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_fisher_cottage_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_tannery_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_cartographer_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_library_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_mason_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_weaponsmith_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_weaponsmith_2", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_temple_1", ProcessorLists::ZOMBIE_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_temple_2", ProcessorLists::ZOMBIE_SAVANNA), 3 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_large_farm_1", ProcessorLists::ZOMBIE_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_large_farm_2", ProcessorLists::ZOMBIE_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_small_farm", ProcessorLists::ZOMBIE_SAVANNA), 4 },
			{JigsawPiece::legacy("village/savanna/houses/savanna_animal_pen_1", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_animal_pen_2", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::legacy("village/savanna/zombie/houses/savanna_animal_pen_3", ProcessorLists::ZOMBIE_SAVANNA), 2 },
			{JigsawPiece::empty(), 5 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/terminators",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/terminators/terminator_01", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_02", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_03", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_04", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/terminators/terminator_05", ProcessorLists::STREET_SAVANNA), 1 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/savanna/zombie/terminators",
		"empty",
		{
			{JigsawPiece::legacy("village/plains/terminators/terminator_01", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_02", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_03", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/plains/terminators/terminator_04", ProcessorLists::STREET_SAVANNA), 1 },
			{JigsawPiece::legacy("village/savanna/zombie/terminators/terminator_05", ProcessorLists::STREET_SAVANNA), 1 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/savanna/trees",
		"empty",
		{
			{JigsawPiece::feature(ConfiguredFeatures::ACACIA), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/savanna/savanna_lamp_post_01"), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::ACACIA), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_HAY), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_MELON), 1 },
			{JigsawPiece::empty(), 4 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/zombie/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/savanna/savanna_lamp_post_01", ProcessorLists::ZOMBIE_SAVANNA), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::ACACIA), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_HAY), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_MELON), 1 },
			{JigsawPiece::empty(), 4 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/savanna/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/savanna/villagers/baby"), 1 },
			{JigsawPiece::legacy("village/savanna/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/savanna/zombie/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/savanna/zombie/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/savanna/zombie/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);
}

void DesertVillagePools::init() {
	create(
		"village/desert/town_centers",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/town_centers/desert_meeting_point_1"), 98 },
			{JigsawPiece::legacy("village/desert/town_centers/desert_meeting_point_2"), 98 },
			{JigsawPiece::legacy("village/desert/town_centers/desert_meeting_point_3"), 49 },
			{JigsawPiece::legacy("village/desert/zombie/town_centers/desert_meeting_point_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/town_centers/desert_meeting_point_2", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/town_centers/desert_meeting_point_3", ProcessorLists::ZOMBIE_DESERT), 1 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/desert/streets",
		"village/desert/terminators",
		{
			{JigsawPiece::legacy("village/desert/streets/corner_01"), 3 },
			{JigsawPiece::legacy("village/desert/streets/corner_02"), 3 },
			{JigsawPiece::legacy("village/desert/streets/straight_01"), 4 },
			{JigsawPiece::legacy("village/desert/streets/straight_02"), 4 },
			{JigsawPiece::legacy("village/desert/streets/straight_03"), 3 },
			{JigsawPiece::legacy("village/desert/streets/crossroad_01"), 3 },
			{JigsawPiece::legacy("village/desert/streets/crossroad_02"), 3 },
			{JigsawPiece::legacy("village/desert/streets/crossroad_03"), 3 },
			{JigsawPiece::legacy("village/desert/streets/square_01"), 3 },
			{JigsawPiece::legacy("village/desert/streets/square_02"), 3 },
			{JigsawPiece::legacy("village/desert/streets/turn_01"), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/desert/zombie/streets",
		"village/desert/zombie/terminators",
		{
			{JigsawPiece::legacy("village/desert/zombie/streets/corner_01"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/corner_02"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/straight_01"), 4 },
			{JigsawPiece::legacy("village/desert/zombie/streets/straight_02"), 4 },
			{JigsawPiece::legacy("village/desert/zombie/streets/straight_03"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/crossroad_01"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/crossroad_02"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/crossroad_03"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/square_01"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/square_02"), 3 },
			{JigsawPiece::legacy("village/desert/zombie/streets/turn_01"), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/desert/houses",
		"village/desert/terminators",
		{
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_2"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_3"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_4"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_5"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_6"), 1 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_7"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_small_house_8"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_medium_house_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_medium_house_2"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_butcher_shop_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_tool_smith_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_fletcher_house_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_shepherd_house_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_armorer_1"), 1 },
			{JigsawPiece::legacy("village/desert/houses/desert_fisher_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_tannery_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_cartographer_house_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_library_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_mason_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_weaponsmith_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_temple_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_temple_2"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_large_farm_1", ProcessorLists::FARM_DESERT), 11 },
			{JigsawPiece::legacy("village/desert/houses/desert_farm_1", ProcessorLists::FARM_DESERT), 4 },
			{JigsawPiece::legacy("village/desert/houses/desert_farm_2", ProcessorLists::FARM_DESERT), 4 },
			{JigsawPiece::legacy("village/desert/houses/desert_animal_pen_1"), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_animal_pen_2"), 2 },
			{JigsawPiece::empty(), 5 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/desert/zombie/houses",
		"village/desert/zombie/terminators",
		{
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_2", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_3", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_4", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_5", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_6", ProcessorLists::ZOMBIE_DESERT), 1 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_7", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_small_house_8", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_medium_house_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/zombie/houses/desert_medium_house_2", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_butcher_shop_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_tool_smith_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_fletcher_house_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_shepherd_house_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_armorer_1", ProcessorLists::ZOMBIE_DESERT), 1 },
			{JigsawPiece::legacy("village/desert/houses/desert_fisher_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_tannery_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_cartographer_house_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_library_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_mason_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_weaponsmith_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_temple_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_temple_2", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_large_farm_1", ProcessorLists::ZOMBIE_DESERT), 7 },
			{JigsawPiece::legacy("village/desert/houses/desert_farm_1", ProcessorLists::ZOMBIE_DESERT), 4 },
			{JigsawPiece::legacy("village/desert/houses/desert_farm_2", ProcessorLists::ZOMBIE_DESERT), 4 },
			{JigsawPiece::legacy("village/desert/houses/desert_animal_pen_1", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::legacy("village/desert/houses/desert_animal_pen_2", ProcessorLists::ZOMBIE_DESERT), 2 },
			{JigsawPiece::empty(), 5 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/desert/terminators",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/terminators/terminator_01"), 1 },
			{JigsawPiece::legacy("village/desert/terminators/terminator_02"), 1 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/desert/zombie/terminators",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/terminators/terminator_01"), 1 },
			{JigsawPiece::legacy("village/desert/zombie/terminators/terminator_02"), 1 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"village/desert/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/desert_lamp_1"), 10 },
			{JigsawPiece::feature(ConfiguredFeatures::PATCH_CACTUS), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_HAY), 4 },
			{JigsawPiece::empty(), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/desert/zombie/decor",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/desert_lamp_1", ProcessorLists::ZOMBIE_DESERT), 10 },
			{JigsawPiece::feature(ConfiguredFeatures::PATCH_CACTUS), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_HAY), 4 },
			{JigsawPiece::empty(), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/desert/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/desert/villagers/baby"), 1 },
			{JigsawPiece::legacy("village/desert/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);

	create(
		"village/desert/zombie/villagers",
		"empty",
		{
			{JigsawPiece::legacy("village/desert/zombie/villagers/nitwit"), 1 },
			{JigsawPiece::legacy("village/desert/zombie/villagers/unemployed"), 10 }
		},
		JigsawProjection::RIGID
	);
}

void TaigaVillagePools::init() {
	create(
		"village/taiga/town_centers", 
		"empty", 
		{
			{JigsawPiece::legacy("village/taiga/town_centers/taiga_meeting_point_1", ProcessorLists::MOSSIFY_10_PERCENT), 49 }, 
			{JigsawPiece::legacy("village/taiga/town_centers/taiga_meeting_point_2", ProcessorLists::MOSSIFY_10_PERCENT), 49 }, 
			{JigsawPiece::legacy("village/taiga/zombie/town_centers/taiga_meeting_point_1", ProcessorLists::ZOMBIE_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/taiga/zombie/town_centers/taiga_meeting_point_2", ProcessorLists::ZOMBIE_TAIGA), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"village/taiga/streets", 
		"village/taiga/terminators", 
		{
			{JigsawPiece::legacy("village/taiga/streets/corner_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/streets/corner_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/streets/corner_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/streets/straight_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/streets/straight_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/streets/straight_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/streets/straight_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 7 }, 
			{JigsawPiece::legacy("village/taiga/streets/straight_05", ProcessorLists::STREET_SNOWY_OR_TAIGA), 7 }, 
			{JigsawPiece::legacy("village/taiga/streets/straight_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/streets/crossroad_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/taiga/streets/crossroad_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/taiga/streets/crossroad_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/streets/crossroad_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/streets/crossroad_05", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/streets/crossroad_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/streets/turn_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);
	create(
		"village/taiga/zombie/streets", 
		"village/taiga/terminators", 
		{
			{JigsawPiece::legacy("village/taiga/zombie/streets/corner_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/corner_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/corner_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/straight_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/straight_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/straight_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/straight_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 7 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/straight_05", ProcessorLists::STREET_SNOWY_OR_TAIGA), 7 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/straight_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/crossroad_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/crossroad_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/crossroad_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/streets/crossroad_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/streets/crossroad_05", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/streets/crossroad_06", ProcessorLists::STREET_SNOWY_OR_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/streets/turn_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 3 }
		},
		JigsawProjection::TERRAIN_MATCHING
	);
	create(
		"village/taiga/houses", 
		"village/taiga/terminators", 
		{
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 4 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_house_2", ProcessorLists::MOSSIFY_10_PERCENT), 4 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_house_3", ProcessorLists::MOSSIFY_10_PERCENT), 4 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_house_4", ProcessorLists::MOSSIFY_10_PERCENT), 4 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_house_5", ProcessorLists::MOSSIFY_10_PERCENT), 4 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_medium_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_medium_house_2", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_medium_house_3", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_medium_house_4", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_butcher_shop_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_tool_smith_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_fletcher_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_shepherds_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_armorer_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 1 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_armorer_2", ProcessorLists::MOSSIFY_10_PERCENT), 1 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_fisher_cottage_1", ProcessorLists::MOSSIFY_10_PERCENT), 3 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_tannery_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_cartographer_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_library_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_masons_house_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_weaponsmith_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_weaponsmith_2", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_temple_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_large_farm_1", ProcessorLists::FARM_TAIGA), 6 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_large_farm_2", ProcessorLists::FARM_TAIGA), 6 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_farm_1", ProcessorLists::MOSSIFY_10_PERCENT), 1 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_animal_pen_1", ProcessorLists::MOSSIFY_10_PERCENT), 2 },
			{JigsawPiece::empty(), 6 }
		},
		JigsawProjection::RIGID);
	create(
		"village/taiga/zombie/houses", 
		"village/taiga/terminators", 
		{
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_small_house_1", ProcessorLists::ZOMBIE_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_small_house_2", ProcessorLists::ZOMBIE_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_small_house_3", ProcessorLists::ZOMBIE_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_small_house_4", ProcessorLists::ZOMBIE_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_small_house_5", ProcessorLists::ZOMBIE_TAIGA), 4 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_medium_house_1", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_medium_house_2", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_medium_house_3", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_medium_house_4", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_butcher_shop_1", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_tool_smith_1", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/houses/taiga_fletcher_house_1", ProcessorLists::ZOMBIE_TAIGA), 2 }, 
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_shepherds_house_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_armorer_house_1", ProcessorLists::ZOMBIE_TAIGA), 1 },
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_fisher_cottage_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_tannery_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_cartographer_house_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_library_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_masons_house_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_weaponsmith_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_weaponsmith_2", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_temple_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_large_farm_1", ProcessorLists::ZOMBIE_TAIGA), 6 },
			{JigsawPiece::legacy("village/taiga/zombie/houses/taiga_large_farm_2", ProcessorLists::ZOMBIE_TAIGA), 6 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_small_farm_1", ProcessorLists::ZOMBIE_TAIGA), 1 },
			{JigsawPiece::legacy("village/taiga/houses/taiga_animal_pen_1", ProcessorLists::ZOMBIE_TAIGA), 2 },
			{JigsawPiece::empty(), 6 }
		},
		JigsawProjection::RIGID
	);
	create(
		"village/taiga/terminators", 
		"empty", 
		{
			{JigsawPiece::legacy("village/plains/terminators/terminator_01", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/plains/terminators/terminator_02", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/plains/terminators/terminator_03", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }, 
			{JigsawPiece::legacy("village/plains/terminators/terminator_04", ProcessorLists::STREET_SNOWY_OR_TAIGA), 1 }
		}, 
		JigsawProjection::TERRAIN_MATCHING
	);
	create(
		"village/taiga/decor", 
		"empty", 
		{
			{JigsawPiece::legacy("village/taiga/taiga_lamp_post_1"), 10 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_1"), 4 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_2"), 1 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_3"), 1 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_4"), 1 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_5"), 2 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_6"), 1 }, 
			{JigsawPiece::feature(ConfiguredFeatures::SPRUCE), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PINE), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_PUMPKIN), 2 },
			{JigsawPiece::feature(ConfiguredFeatures::PATCH_TAIGA_GRASS), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PATCH_BERRY_BUSH), 1 },
			{JigsawPiece::empty(), 4 }
		},
		JigsawProjection::RIGID
	);
	create(
		"village/taiga/zombie/decor", 
		"empty", 
		{
			{JigsawPiece::legacy("village/taiga/taiga_decoration_1"), 4 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_2"), 1 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_3"), 1 }, 
			{JigsawPiece::legacy("village/taiga/taiga_decoration_4"), 1 }, 
			{JigsawPiece::feature(ConfiguredFeatures::SPRUCE), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PINE), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PILE_PUMPKIN), 2 },
			{JigsawPiece::feature(ConfiguredFeatures::PATCH_TAIGA_GRASS), 4 },
			{JigsawPiece::feature(ConfiguredFeatures::PATCH_BERRY_BUSH), 1 },
			{JigsawPiece::empty(), 4 }
		}, 
		JigsawProjection::RIGID
	);
	create(
		"village/taiga/villagers", 
		"empty", 
		{
			{JigsawPiece::legacy("village/taiga/villagers/nitwit"), 1 }, 
			{JigsawPiece::legacy("village/taiga/villagers/baby"), 1 }, 
			{JigsawPiece::legacy("village/taiga/villagers/unemployed"), 10 }
		}, 
		JigsawProjection::RIGID
	);
	create(
		"village/taiga/zombie/villagers", 
		"empty", 
		{
			{JigsawPiece::legacy("village/taiga/zombie/villagers/nitwit"), 1 }, 
			{JigsawPiece::legacy("village/taiga/zombie/villagers/unemployed"), 10 }
		}, 
		JigsawProjection::RIGID
	);
}

void PillagerOutpostPools::init() {
	create(
		"pillager_outpost/base_plates", 
		"empty", 
		{
			{ JigsawPiece::legacy("pillager_outpost/base_plate"), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"pillager_outpost/towers", 
		"empty", 
		{
			{
				JigsawPiece::list({
					JigsawPiece::legacy("pillager_outpost/watchtower"), 
					JigsawPiece::legacy("pillager_outpost/watchtower_overgrown", ProcessorLists::OUTPOST_ROT)
				}), 
				1
			}
		}, 
		JigsawProjection::RIGID
	);

	create(
		"pillager_outpost/feature_plates", 
		"empty", 
		{
			{ JigsawPiece::legacy("pillager_outpost/feature_plate"), 1 }
		}, 
		JigsawProjection::TERRAIN_MATCHING
	);

	create(
		"pillager_outpost/features", 
		"empty", 
		{
			{ JigsawPiece::legacy("pillager_outpost/feature_cage1"), 1 }, 
			{ JigsawPiece::legacy("pillager_outpost/feature_cage2"), 1 }, 
			{ JigsawPiece::legacy("pillager_outpost/feature_logs"), 1 }, 
			{ JigsawPiece::legacy("pillager_outpost/feature_tent1"), 1 }, 
			{ JigsawPiece::legacy("pillager_outpost/feature_tent2"), 1 }, 
			{ JigsawPiece::legacy("pillager_outpost/feature_targets"), 1 }, 
			{ JigsawPiece::empty(), 6 }
		}, 
		JigsawProjection::RIGID
	);
}

void BastionRemnantsPieces::init() {
	create(
		"bastion/starts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/air_base", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/air_base", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/treasure/big_air_full", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/bridge/starting_pieces/entrance_base", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	// BastionRemnantsMainPools
	create(
		"bastion/units/center_pieces", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/center_pieces/center_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/center_pieces/center_1", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/center_pieces/center_2", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/pathways", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/pathways/pathway_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/pathways/pathway_wall_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/walls/wall_bases", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/walls/wall_base", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/walls/connected_wall", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/stages/stage_0", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/stages/stage_0_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_0_1", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_0_2", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_0_3", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/stages/stage_1", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/stages/stage_1_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_1_1", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_1_2", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_1_3", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/stages/rot/stage_1", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/stages/rot/stage_1_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/stages/stage_2", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/stages/stage_2_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_2_1", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/stages/stage_3", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/stages/stage_3_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_3_1", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_3_2", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/stages/stage_3_3", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/fillers/stage_0", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/fillers/stage_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/edges", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/edges/edge_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/wall_units", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/wall_units/unit_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/edge_wall_units", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/wall_units/edge_0_large", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/ramparts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/ramparts/ramparts_0", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/ramparts/ramparts_1", ProcessorLists::HOUSING), 1 }, 
			{ JigsawPiece::single("bastion/units/ramparts/ramparts_2", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/large_ramparts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/ramparts/ramparts_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/units/rampart_plates", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/units/rampart_plates/plate_0", ProcessorLists::HOUSING), 1 }
		}, 
		JigsawProjection::RIGID
	);

	// BastionRemnantsStablesPools
	create(
		"bastion/hoglin_stable/starting_pieces", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/starting_stairs_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/starting_stairs_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/starting_stairs_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/starting_stairs_3", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/starting_stairs_4", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/mirrored_starting_pieces", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/stairs_0_mirrored", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/stairs_1_mirrored", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/stairs_2_mirrored", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/stairs_3_mirrored", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/starting_pieces/stairs_4_mirrored", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/wall_bases", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/walls/wall_base", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/walls", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/walls/side_wall_0", ProcessorLists::SIDE_WALL_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/walls/side_wall_1", ProcessorLists::SIDE_WALL_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/stairs", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_1_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_1_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_1_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_1_3", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_1_4", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_2_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_2_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_2_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_2_3", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_2_4", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_3_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_3_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_3_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_3_3", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/stairs/stairs_3_4", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/small_stables/inner", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/inner_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/inner_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/inner_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/inner_3", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/small_stables/outer", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/outer_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/outer_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/outer_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/small_stables/outer_3", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/large_stables/inner", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/inner_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/inner_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/inner_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/inner_3", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/inner_4", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/large_stables/outer", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/outer_0", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/outer_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/outer_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/outer_3", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/large_stables/outer_4", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/posts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/posts/stair_post", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/posts/end_post", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/ramparts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/ramparts/ramparts_1", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/ramparts/ramparts_2", ProcessorLists::STABLE_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/hoglin_stable/ramparts/ramparts_3", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/rampart_plates", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/rampart_plates/rampart_plate_1", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/hoglin_stable/connectors", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/hoglin_stable/connectors/end_post_connector", ProcessorLists::STABLE_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	// BastionRemnantsTreasurePools
	create(
		"bastion/treasure/bases", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/bases/lava_basin", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/stairs", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/stairs/lower_stairs", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/bases/centers", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/bases/centers/center_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/bases/centers/center_1", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/bases/centers/center_2", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/bases/centers/center_3", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/brains", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/brains/center_brain", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/walls", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/walls/lava_wall", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/entrance_wall", ProcessorLists::HIGH_WALL), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/walls/outer", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/walls/outer/top_corner", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/outer/mid_corner", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/outer/bottom_corner", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/outer/outer_wall", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/outer/medium_outer_wall", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/outer/tall_outer_wall", ProcessorLists::HIGH_WALL), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/walls/bottom", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/walls/bottom/wall_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/bottom/wall_1", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/bottom/wall_2", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/bottom/wall_3", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/walls/mid", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/walls/mid/wall_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/mid/wall_1", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/mid/wall_2", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/walls/top", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/walls/top/main_entrance", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/top/wall_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/walls/top/wall_1", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/connectors", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/connectors/center_to_wall_middle", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/connectors/center_to_wall_top", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/connectors/center_to_wall_top_entrance", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/entrances", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/entrances/entrance_0", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/ramparts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/ramparts/mid_wall_main", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/ramparts/mid_wall_side", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/ramparts/bottom_wall_0", ProcessorLists::BOTTOM_RAMPART), 1 }, 
			{ JigsawPiece::single("bastion/treasure/ramparts/top_wall", ProcessorLists::HIGH_RAMPART), 1 }, 
			{ JigsawPiece::single("bastion/treasure/ramparts/lava_basin_side", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/ramparts/lava_basin_main", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/corners/bottom", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/corners/bottom/corner_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/corners/bottom/corner_1", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/corners/edges", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/corners/edges/bottom", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/corners/edges/middle", ProcessorLists::HIGH_WALL), 1 }, 
			{ JigsawPiece::single("bastion/treasure/corners/edges/top", ProcessorLists::HIGH_WALL), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/corners/middle", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/corners/middle/corner_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/corners/middle/corner_1", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/corners/top", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/corners/top/corner_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/corners/top/corner_1", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/extensions/large_pool", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/extensions/empty", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/empty", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/fire_room", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/large_bridge_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/large_bridge_1", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/large_bridge_2", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/large_bridge_3", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/roofed_bridge", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/empty", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/extensions/small_pool", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/extensions/empty", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/fire_room", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/empty", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/small_bridge_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/small_bridge_1", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/small_bridge_2", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/small_bridge_3", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/extensions/houses", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/extensions/house_0", ProcessorLists::TREASURE_ROOMS), 1 }, 
			{ JigsawPiece::single("bastion/treasure/extensions/house_1", ProcessorLists::TREASURE_ROOMS), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/treasure/roofs", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/treasure/roofs/wall_roof", ProcessorLists::ROOF), 1 }, 
			{ JigsawPiece::single("bastion/treasure/roofs/corner_roof", ProcessorLists::ROOF), 1 }, 
			{ JigsawPiece::single("bastion/treasure/roofs/center_roof", ProcessorLists::ROOF), 1 }
		}, 
		JigsawProjection::RIGID
	);

	// BastionRemnantsBridgePools
	create(
		"bastion/bridge/starting_pieces", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/starting_pieces/entrance", ProcessorLists::ENTRANCE_REPLACEMENT), 1 }, 
			{ JigsawPiece::single("bastion/bridge/starting_pieces/entrance_face", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/bridge/bridge_pieces", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/bridge_pieces/bridge", ProcessorLists::BRIDGE), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/bridge/legs", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/legs/leg_0", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/bridge/legs/leg_1", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/bridge/walls", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/walls/wall_base_0", ProcessorLists::RAMPART_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/bridge/walls/wall_base_1", ProcessorLists::RAMPART_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/bridge/ramparts", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/ramparts/rampart_0", ProcessorLists::RAMPART_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/bridge/ramparts/rampart_1", ProcessorLists::RAMPART_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/bridge/rampart_plates", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/rampart_plates/plate_0", ProcessorLists::RAMPART_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/bridge/connectors", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/bridge/connectors/back_bridge_top", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }, 
			{ JigsawPiece::single("bastion/bridge/connectors/back_bridge_bottom", ProcessorLists::BASTION_GENERIC_DEGRADATION), 1 }
		}, 
		JigsawProjection::RIGID
	);

	// BastionRemnantsMobsPools
	create(
		"bastion/mobs/piglin", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/mobs/melee_piglin"), 1 }, 
			{ JigsawPiece::single("bastion/mobs/sword_piglin"), 4 }, 
			{ JigsawPiece::single("bastion/mobs/crossbow_piglin"), 4 }, 
			{ JigsawPiece::single("bastion/mobs/empty"), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/mobs/hoglin", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/mobs/hoglin"), 2 }, 
			{ JigsawPiece::single("bastion/mobs/empty"), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/blocks/gold", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/blocks/air"), 3 }, 
			{ JigsawPiece::single("bastion/blocks/gold"), 1 }
		}, 
		JigsawProjection::RIGID
	);

	create(
		"bastion/mobs/piglin_melee", 
		"empty", 
		{
			{ JigsawPiece::single("bastion/mobs/melee_piglin_always"), 1 }, 
			{ JigsawPiece::single("bastion/mobs/melee_piglin"), 5 }, 
			{ JigsawPiece::single("bastion/mobs/sword_piglin"), 1 }
		}, 
		JigsawProjection::RIGID
	);
}