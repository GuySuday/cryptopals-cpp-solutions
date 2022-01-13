#include <gtest/gtest.h>
#include <cstdint> // std::uint64_t

using std::uint64_t;

#include "utils/base_conversions.hpp"

class BinaryToDecimalTestFixture : public ::testing::TestWithParam<std::tuple<std::string, uint64_t>> {};
class BinaryToHexTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};
class HexToBinaryTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};
class Base64ToHexTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};

// TODO: is there a way to combine the fixture tests (TEST_P) and the regular tests (TEST) under the same name?
TEST(BaseConversions, hex_to_binary_invalid_hex)
{
    std::string invalid_hex = "not hex";
    EXPECT_THROW(
        base_conversions::hex_to_binary(invalid_hex),
        std::invalid_argument
    );
}
TEST_P(HexToBinaryTestFixture, hex_to_binary)
{
    std::string hex = std::get<0>(GetParam());
    std::string expected_binary = std::get<1>(GetParam());

    std::string binary = base_conversions::hex_to_binary(hex);

    EXPECT_EQ(binary, expected_binary);
}
TEST_P(BinaryToDecimalTestFixture, binary_to_decimal)
{
    std::string binary = std::get<0>(GetParam());
    uint64_t expected_decimal = std::get<1>(GetParam());;

    uint64_t decimal = base_conversions::binary_to_decimal(binary);
    EXPECT_EQ(decimal, expected_decimal);
}

TEST(BaseConversions, binary_to_hex_wrong_length)
{
    std::string binary = "010";

    EXPECT_THROW(
        base_conversions::binary_to_hex(binary),
        std::invalid_argument
    );
}

TEST_P(BinaryToHexTestFixture, binary_to_hex)
{
    std::string binary = std::get<0>(GetParam());
    std::string expected_hex = std::get<1>(GetParam());

    std::string hex = base_conversions::binary_to_hex(binary);
    EXPECT_EQ(hex, expected_hex);
}

TEST_P(Base64ToHexTestFixture, base64_to_hex)
{
    std::string base64 = std::get<0>(GetParam());
    std::string expected_hex = std::get<1>(GetParam());

    std::string hex = base_conversions::base64_to_hex(base64);
    EXPECT_EQ(hex, expected_hex);
}

INSTANTIATE_TEST_SUITE_P(
    BaseConversions,
    Base64ToHexTestFixture,
    ::testing::Values(
        std::make_tuple(
            "",
            ""
        ), // empty_str
        std::make_tuple(
            "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t",
            "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
        ), // s01c01 cryptopals_example
        std::make_tuple(
            "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",
            "1d421f4d0b0f021f4f134e3c1a69651f491c0e4e13010b074e1b01164536001e01496420541d1d4333534e6552060047541c0d454d07040c53123c0c1e08491a09114f144c211a472b00051d47591104090064260753003716060c1a17411d015254305f0020130a05474f124808454e653e160938450605081a46074f1f59787e6a62360c1d0f410d4806551a1b001d4274041e01491a091102527a7f4900483a001a13491a4f45480f1d0d53043a015219010b411306004c315f53621506070907540b17411416497933350b1b01050f46074f1d4e784e48275204070c4558480841004f205408740b1d194902000e165c00523069651f4902025400010b074e021053012610154d0207021f4f1b4e78306936520a010954060709534e021053083b100605490f0f104f3b003a5f472b1c4964334f540210531a4f051611740c064d0f020e0343524c3d4e002f0b490d084e170d15541d4f0e1c455e280b4d190112070a5553784e4f6206010b47531d0c0000170a051f0c3a425e4d2e0141220e1c493456416235064f472a7e3b084f011b0153423704071e0c4e151c0e06072b1a542a17491906595421455707030553073145782c070a411d095259374f00261d07491300130113454e0e491704390b5e4d1d06041a4f78773043003b1d1c4e1454151a0c4e494f080745390052673a0141130a0600375c4662550a0f125311482c000d000707173b095219010b41071b13473d1a2a161a0c1c020707480b4f4e0b0000163d0b554d08020d1b181744783069651f490709001911454f190149030d3516174d633a09114f15492a56492701491d06000d4811480b16491f0a220052000c4e001a0b5254305b54621b1a4e084b5462244e0a4f205306350b5209080002114f10452c4e4530521d06064e54090b594e040017453a42521d050f18546578732c5b4727525b4e4a0d543100414e1b0116453b0b174d100f465418134e365b002e1b1a1a024e541c0a0064261d5416740a140b490318540717413c1a532d52050b1300000000000c0a08074524091314491a0906000747301a2a111d49274743150645461b0102530c2045071d490f0f104f1f41335f002b06491d08551a0c454701000d536f654840405a4e381b4f5f0d78714e2d11024e084e541b0a4d0b4f1e1c0a3045782b061c4113001d447856552119454e2e0018010e454e021053173c1c1f081a4e00001d1d433155553152633d1250111a0641020e0f0104330c1e041a1a08170a0a50315b4c2b16060d0e4f011b452a27480453043a45170b0f0b02004f134e3c1a542a131d4e1e4f01480641004f0b1611746f3b4d0a0f0f541b134b3d1a416214051747471d1a09000f010d5308350e174d010b1354181754761a2a483b4e03474c1d0300003d0e04000a3a455f40493d00191c1d4e784e4f62360c020e4c1500452a3a070c010073165203064e0511010b49361d0c622b061b4743150645541c1649070a740d13030e4e6b361a0600215555651e054e0c45111845541c16001d4274111d4d0e0b1554020b002b4e592e1749642856111a4541000b491c1331175e4d191c00171b1b433d1a4d23190c1d4750111a03450d1b49792721115203061a411d095259374f073017490f474c1b0903451c4149796f0d0a074a050241130a06003655572a171b0b4b001a074550020e0a1649740b1d4d1d070c1143524e371a472b00051d472a27070a4e4e4244532a3c451f1449290e10435248375745201d0d174b000d0710001e1d06110436090b4d0c0f1554652150395d4827061d0747571d1c0d000f4f1a030a3b0b534d2a010c114f1d4e785b4e26521a0f1e001d1c440064653f3a357a45240c07070d180e52693b5f003b17194247591118490027480453063b081b034e4e09151d160034534b2752084e15481d060a00642607070a2c0c110c1d070f134f014f78434f37521a1a0647130d17000206021645354505040701417e3c1d00284f4e2901491d134f044811521706071445350b164d0e0713184f0154374a00210010070907546233410006051f04742c1108490712541c174c34534e6552080003000d0710001e0a0603093145131f0c4e0301161b4e7f1a2a6531081b1445541f0d594e1b0116453217170c021d41151d1700325543291b0749474c1d0300002d1d08091c74221e180c4e6b39000449361d00231c0d4e00521b07134900484907172d0c1c0a491a0e541c1b4e3f1a412e1d0709472a350409001a071b1c10330d5219010b41130717542c55002500060111491a4f455406061a530d3117174d1a010f134f786e374d003b1d1c49154554090841140a0d53072d4506050c4e373d3f5250374953275c49646d73000d155007014e53163b451a0c1b0a4118061945785b0005171b03064e5426045a074f632011351706010c0a4116165254305f0020131a0b14001c01115407014e5302260a07030d4e6b200717523d1d53621c064e13521d1815490048491c0b74081b030c42413d481f00324f5336520e0b13541d0642000a001e1d455e36020c1b0500190e06493b16000b55044e0f411a0f0c4e494f1d1a023c115201000504540e5246395441361b0a4e6d791b1d45541c0e19030030451f0849010f170a5241365e000b521d060855130011001a070807455e3c1d1849030813070600305b562752001a472a270745531a0a1953013b121c4d0800055403174e3c1a4d275210011252540d04524e654e4b5c740c1c4d04174100061f45791a792d07454e401944480c534e0210531c3104004349646b2d0007072a5f0035170805024e1d064200080e1a0749743c3d4c490f0f104f3b003b5b4e62060c020b001d1c452a37001c0145360a16144e1d41130a0654315407621a061a4b00070749001d00493a4537041c4d1a0304180352492c1a2a111d490a084e531c45420b4f04120174041c09490a0e1a4806003a5f0031130d4e6d07370910530b4f1d1b0074090b1f000d12540d174c3754476206064e2e6331444579011a4910043a45110c050241190a5264395e00482b061b4052114815491a0c011a0b7345134d0f0715584f014f7849542702490c06431f48044e0a4f0c1d012117174d632204004f06483d1a572b060a0647441b0b114f1c43493a0631495209064e151c0a524439544327521d014743011a0000643c0653063b08174d1c1e4117031d533d1a412c16490a084e531c45420b4f1a02103517174d63370e014f05413654416210081a134c114808454e424453243a1c0604040b4d540e1c592f5245301749646d791b1d455406001c140d20450605081a413d4f05412b1a572713024247621b11490017001c541731451608080a41031d1d4e3f1a2a111d490d084d11480a4e424f0c0500261c10020d1741150116002b534e25521d060e53541b0a4e094f637936351c5240444e31180e0b002c524136520f1b094b0d4808551d060a5336351c5e4d0e014103071b543d1a422d0b454e004f541f0d491a0a49110a2d451502496411180e0b002c524136520f1b094b0d4808551d060a53223b450505001a04540d1d59741a472d521e060e541148074f174349140a746f3e0c104e051b181c003954446210060100491148044e0a4f191f042d450605081a41121a1c4b211a4d3701000d47541d04090017001c53013d005c4d636431180e0b002c524136520f1b094b0d4808551d060a53263b08174d06004d542c1d4d3d1a4f2c5e4902025454050000060a0801455e351e0c104e151c0e06003e4f4e290b490312531d0b455706061d1645360a0b4d100114541c13597853546e521a0f1e001d1c452a3e03080a45200d13194908141a040b00354f532b11492f474c1d1c114c0b4f051c103000004d0701165465224c394300361a081a474601060e594e021c000c3749521a010715114f104f211a632d1f0c4e084e5848264f030a491c0b78453102040b411b01522a0856413b521d060654540e104e0516491e10270c114d63"
        ), // s01c06 cryptopals_example
        std::make_tuple(
            "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",
            "091230aade3eb330dbaa4358f88d2a6c37b72d0cf4c22c344aec4142d00ce530dd31b8c2303fef7a75035bd04b3c45ce0db93a6b8f2831b018e830d9b2e2db734b91f5ca7d850d10406013cb20844aad8d4acbe1c79cca94bb7376c9df2b9103e6caca8caec5cf8437f3fb6d77eb2d2fff569c3ce526f028ed606c8c8e5825cda098061ac8d7e6096da585913f64b1b40810f668fc345b8d7b4186f870020e5bdda3611889e0f4ec0411c37bca38270a9a51a73aaea762f37de46f200e57f63644c6cdd280dbf51abcb911ef6eba9025a26279ab3012d324814b773f94ed81e87b27e844e93474b87a2df16cc7c8028d6d4587a22ff9cdc442522a6f54e60ba0165794dbb8aa7c28099452060bc2c13773dc26eca7f3f6c1707cb62cfa97dacbd9b2e106dd77431ca186ed07d3e24a8fab2849e5f9643d51a62969f67711d6d1d6f3ebaead02b25cde3129e1a368a2ce7a3af6c43230f9a585ec6b33538a898570675d321450d51f465c04a52e8565cb0ccde990177d1ecd22477e95bb0d51f3c222f27a24c944aa15530a38dcf5eea672570e6532b026b69d0cff884c32a2bea43de90bbf572c9b53dad8b6666c0f548f3cfccdbfe0157b50a8100de3303cff0b7455fa0eb0467072c68b39650fb45fd1cb756194ac1713b8061ff6db4a1008290a8caaa52412e719dc73c7015a7b6429f73b1ebe739409dd4bfc57b2fb4a9ae87cf14de85fa47c3338cc0739f5da39b70803a029426f1c46d0bd7d4c11878983f70b281e6351cb32b5fa2aaca925f1495b93bdc0d205d2a7ce0b6956160c1ac8ec2ae35c5d152096d3f10149cedc270dcdd3a59386b5b92e29803ade4bf5cec8938608c6ed0af496700317dc5384a162ee9eb989962cff7cfaabd19c8ad791e3ee812f5348e24e1f3294a0e71bd7f29877d35914711ca79f037faad7162cfd0d2abcd2b47929fb3e33e56eab967acd8f7cfd23f403a51122bf4d16ef82b3dfe07feab84d1c2c3b344c8cc43324bf1fed35cf1071f6faa11ca432b3ff9a44d1cbeb807afadd72aee176f32c2381cf40e8140c37be4bb11b026ae02a7192df9e0adc52294ccdb57327fe66cfa8f978359349f32ccca931523834b86d84c168dfee41870e005dcd05815de71f53cc80285ba6a2d776bc87fb3d8b91655512437b671eb50840aeb21506ab85d0bd2651731634f14a91a40406cc69302621ee9a7b625c8236875ed769398d8d7f95cf2340b409f8424774274ce6ddde991ce43e0343e1aece361a08914512d91d68115d6da038fd883cc6545c0ebd6cade06cc0f577714f7df7254fe7f26f8dea1b36dcc05c674f3a929f6b2465716797fcd23473dd972353acd68d1f6e711ca36ecb959f5b78109126e80eca6879b5de6d2fc0dfcee0a6138a263768edec89aca336bacd0699f539e2eff5452778b482771714aa346f3ab740e4d62fdb91dbe30905088842fd8db37bf90dca2b3a16b5ed4ad723282d70f4a83c3b6e555c1d459a9bbee27ce96cd749f4b5da845ef08ce3d737a762c552a9cf04d88c414348c68c85a4ce4c26aa26283defadb8c2fefd5116c282ccb3c1a0bb61746d6d3b2d6c5b8414179edee5bb077c57c3bda6ca6336052dae3d0e4d23099a71b86d6bc682450106a88674efc62bace9592236abde56d30a8e68ea76db0eaf5bbe2962ad61bf4a058836e737a569790ac711720410369ee82c182b4a4424bfd02365872f8ac9ebf3d4f18e8c413b463dde3829e13d782e7570590571de5ddde92d7096c72275579a336e04fc9b52f24f5702f812a0a0a3ca2aac6b004ccd271708844293a9ea5fc65a254deb6742de38c4d4c3a302e1d0be698f52ac2bcd42e6f5f6605db495303813aa19d7dde48a2a42468be837ce926a67b02b393ee2db19905585a8792fcec863bafa4c1d55eca6e85c7f0f64861cd7395e98c646534a3bf9eb716561e0a5d797e896c922cde2940cd8ab0fc7cfae67a3b794c5c0e0d5a39ac5e9ae3ea9d8446856e8fbe365bc00b5f40f9687e10748d31ede5b465cc5d7bae7f6affac3395cd6cb29db199e1735e8c5f7e910b00157afb28f781f43f6f1201f4d5a37592b4f115fdae39bd09c06545079366b0faed26105aa4694f9b7bcdc5439f1d6ced97df2c15a6fef5cb7cfccc69060427811fa1db92bad8ec857bd1f954113ecd9359c17b3ac684e1cb1e74a50616ea3d0d87c5207143360fb53f2ae5589d09fd7d0f76e02e099fae412b0cfdec7fbdf5e9e99dfd9e0ab87b1517a0fb4022a69fac331df12b80b7211987263d57d2e9daa3500db97a248dfd6c3cfeea90e68c9da3967a4c09ecd12bcf5c1b5d48aa2516bc83f11e3a224f582e1f5ba4e2c4363dcd49e338c936c660a090dc3c16dfb2ce2402a509bd0c856f35ac861b55780bf776683050434884d2bf7ab8e9830d812116b2cd8c34d358c0205e5ceeb620dfca3ac7761d02d537777429bb01b9c437ce0f1cdf2f7c84290af8f02fcaab123ceee1b0ca0e87e6073601c2d4f4962de50a031680bb3c5c5c137455a9ceff526f49b3d5fd532ae21237ed5adf3afed1321bb17db561b118d119a3730ec9dc17ffb8edc28c50139c9b1635a776a2e9f035779da2d0b21fc5cfc2674d81ef391ef6bee8b0ff1e43e4f16e5d5d1a495be6c395a76f4f6afc1a304b5e16ce81c7e9e91a59b87bf31972a67fcbfccfa7208117d4e9774da54ea88c6f5d9dac8e6f3ac51cf411da0715fba949e91d0542c2aa9b71a45a41b21645bdab941fc133ef003bc232fae465656747fbe14ecc255bbd4b0b19760b0b9a7b10bebe67da88cd34112ffaa286db0a5461399645a45ce440a550d7e1ce1f220dd1c8b25e9e74e7b039146b36205acb5342ce57f3d5c8fa56561841433d6c3132aabc0ee34d1740da6814ec68e1fc5475df801e60818476f2091f35fc2e8b4131b625006f8f2906e299a8aa760fc43c9e882106f8914798fd482fe8e081d8d684b5906adb25ad6c6e112125dcf12cac090c17b82dd1d04b8275ac735726ce7b46d6b957562fc7b364c053747112631258316e6d28af2d64aa663fd77c65b05693fa7ec9ec7f1a58dddde1fdf4f10eeed4f0675d685450849fb464e771ea7449516deeeb19e11f799855193cf0432da44a4aad22167d7a6180350f6747f86a04737a1927f6fb730a636316741bd3fb219ea4e1e0ca3ff28a2699bb014d428f612effd684028b5d900018c90edf8bc946a7fb88b0bc28b4934214207be4db5dfcd6f0b48b1603671cd8eb8fb1c7f44d203fa2a65833abd3c36608dcf0bee3320fb6fa6af13d2e7a7bbd66e44db3b9f67877e9c58c883e7470ff4a134fcd5a578b3455504473b4bb9a93c02c6a1dffcafc0eac7d6628430c182d7feaa7ef6548052c91f9574129d27d8afc56ecd1596310d20df1c8e408a746f1a06779f121213755ec25635dc8af43a79f91b39009f91f7305a9681142f2d0ffcde6d7144f89b215b5e83e045973274a6ffd1dc1b01efb65023d38af0ad9e6d46f0207f5211f3792aaa24efa9f10d723edd742170b4d66b40aec4261801e53af5b4115c6fd2273d1b52dca62d7981e5dc7591f6df04d98184f081ab4b5b1089bc5a2bf0b490a6ea22b2a99e9c2da0e2ec64f35b3f0e8ada3a64a3d35e640c7b3d81666a64780f9d0ab738042d071a12c8b9682ced320edfa7598aea28f230a2112b034a2181da8114552cd8102e0fd64cacc655b5b0aba910690c80af0402517a38b91b72cc631a29b4c6e1d9ecd4e141d60ecd0a23dbeacd65bf4fe51c5005e87c28615fc53d22ffa62af1c834816ff151440dcf21f9af19f3141855569724bbf8eef7979a08247c6e689ad1e047a7cc0bb802fa5ae5df95ba261b335d1a2da55e8153ef167e2908fe14fcd6dbc383930855f61ca9961225410743b727dc705d6a7137556be420e2ef916a361c580a381227358e503df86357407dc8f9ed520d9905445b273c4dc87cbe0f4c9c718239f3a346aa74546c804b5e40543d904b557a7e1462989495c93e90b866fcb4a46c97637e6b65f37b7eaf80c870ed72bbce1fff8c2d87"
        ), // s01c07 cryptopals_example
        std::make_tuple(
            "O3NsZGpmIG9zZGogcG1wc2RtZnBvc29wZHZmbXNkb3B2ZnA=",
            "3b736c646a66206f73646a20706d7073646d66706f736f706476666d73646f70766670"
        ), // one_padding
        std::make_tuple(
            "O3NsZGpmIG9zZGptIHBtNTh2cDlzZG1mcG9zb3BkdmZtc2RvcHZmcA==",
            "3b736c646a66206f73646a6d20706d353876703973646d66706f736f706476666d73646f70766670"
        ) // two_padding
    )
);

INSTANTIATE_TEST_SUITE_P(
    StringConversions,
    HexToBinaryTestFixture,
    ::testing::Values(
        std::make_tuple(
            "",
            ""
        ),
        std::make_tuple(
            "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d",
            "010010010010011101101101001000000110101101101001011011000110110001101001011011100110011100100000011110010110111101110101011100100010000001100010011100100110000101101001011011100010000001101100011010010110101101100101001000000110000100100000011100000110111101101001011100110110111101101110011011110111010101110011001000000110110101110101011100110110100001110010011011110110111101101101"
        )
    )
);

INSTANTIATE_TEST_SUITE_P(
    StringConversions,
    BinaryToHexTestFixture,
    ::testing::Values(
        std::make_tuple(
            "",
            ""
        ),
        std::make_tuple(
            "010010010010011101101101001000000110101101101001011011000110110001101001011011100110011100100000011110010110111101110101011100100010000001100010011100100110000101101001011011100010000001101100011010010110101101100101001000000110000100100000011100000110111101101001011100110110111101101110011011110111010101110011001000000110110101110101011100110110100001110010011011110110111101101101",
            "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
        ),
        std::make_tuple(
            "0000101100110110001101110010011100101010001010110010111001100011011000100010110000101110011010010110100100101010001000110110100100111010001010100011110001100011001001000010000000101101011000100011110101100011001101000011110000101010001001100010001001100011001001000010011100100111011001010010011100101010001010000010101100101111001000000110100100001010011001010010111000101100011001010010101000110001001001000011001100111010011001010011111000101011001000000010011101100011000011000110100100101011001000000010100000110001011001010010100001100011001001100011000000101110001001110010100000101111",
            "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20690a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"
        )
    )
);
INSTANTIATE_TEST_SUITE_P(
    StringConversions,
    BinaryToDecimalTestFixture,
    ::testing::Values(
        std::make_tuple("", 0),
        std::make_tuple("0", 0),
        std::make_tuple("10", 2),
        std::make_tuple("100", 4),
        std::make_tuple("0100", 4),
        std::make_tuple("1101", 13),
        std::make_tuple("1111", 15),
        std::make_tuple("10000", 16),
        std::make_tuple("10101", 21),
        std::make_tuple("100000", 32),
        std::make_tuple("111111", 63),
        std::make_tuple("1000000", 64),
        std::make_tuple("10000001", 129)
    )
);
