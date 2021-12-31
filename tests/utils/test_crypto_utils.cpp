#include <gtest/gtest.h>

#include <vector> // std::vector
#include <string> // std::string
#include <tuple> // std::tuple

#include "utils/crypto_utils.hpp"
#include "utils/base_string_conversions.hpp"
#include "utils/types.hpp" // bit, byte, uint

class HammingDistanceTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string, uint>> {};
TEST_P(HammingDistanceTestFixture, hamming_distance_)
{
    std::string bits1_str = std::get<0>(GetParam());
    std::string bits2_str = std::get<1>(GetParam());
    uint expected_difference = std::get<2>(GetParam());

    std::vector<bit> bits1(bits1_str.begin(), bits1_str.end());
    std::vector<bit> bits2(bits2_str.begin(), bits2_str.end());
    uint difference = crypto_utils::hamming_distance(bits1, bits2);
    EXPECT_EQ(difference, expected_difference);
}

INSTANTIATE_TEST_SUITE_P(
    CryptoUtils,
    HammingDistanceTestFixture,
    ::testing::Values(
        std::make_tuple("", "", 0),
        std::make_tuple("010", "010", 0),
        std::make_tuple("10", "11", 1),
        std::make_tuple("0111010001101000011010010111001100100000011010010111001100100000011000010010000001110100011001010111001101110100", "0111011101101111011010110110101101100001001000000111011101101111011010110110101101100001001000010010000100100001", 37)
    )
);

TEST(CryptoUtils, aes_ecb_decrypt)
{
    std::string ciphertext_str = "091230aade3eb330dbaa4358f88d2a6c37b72d0cf4c22c344aec4142d00ce530dd31b8c2303fef7a75035bd04b3c45ce0db93a6b8f2831b018e830d9b2e2db734b91f5ca7d850d10406013cb20844aad8d4acbe1c79cca94bb7376c9df2b9103e6caca8caec5cf8437f3fb6d77eb2d2fff569c3ce526f028ed606c8c8e5825cda098061ac8d7e6096da585913f64b1b40810f668fc345b8d7b4186f870020e5bdda3611889e0f4ec0411c37bca38270a9a51a73aaea762f37de46f200e57f63644c6cdd280dbf51abcb911ef6eba9025a26279ab3012d324814b773f94ed81e87b27e844e93474b87a2df16cc7c8028d6d4587a22ff9cdc442522a6f54e60ba0165794dbb8aa7c28099452060bc2c13773dc26eca7f3f6c1707cb62cfa97dacbd9b2e106dd77431ca186ed07d3e24a8fab2849e5f9643d51a62969f67711d6d1d6f3ebaead02b25cde3129e1a368a2ce7a3af6c43230f9a585ec6b33538a898570675d321450d51f465c04a52e8565cb0ccde990177d1ecd22477e95bb0d51f3c222f27a24c944aa15530a38dcf5eea672570e6532b026b69d0cff884c32a2bea43de90bbf572c9b53dad8b6666c0f548f3cfccdbfe0157b50a8100de3303cff0b7455fa0eb0467072c68b39650fb45fd1cb756194ac1713b8061ff6db4a1008290a8caaa52412e719dc73c7015a7b6429f73b1ebe739409dd4bfc57b2fb4a9ae87cf14de85fa47c3338cc0739f5da39b70803a029426f1c46d0bd7d4c11878983f70b281e6351cb32b5fa2aaca925f1495b93bdc0d205d2a7ce0b6956160c1ac8ec2ae35c5d152096d3f10149cedc270dcdd3a59386b5b92e29803ade4bf5cec8938608c6ed0af496700317dc5384a162ee9eb989962cff7cfaabd19c8ad791e3ee812f5348e24e1f3294a0e71bd7f29877d35914711ca79f037faad7162cfd0d2abcd2b47929fb3e33e56eab967acd8f7cfd23f403a51122bf4d16ef82b3dfe07feab84d1c2c3b344c8cc43324bf1fed35cf1071f6faa11ca432b3ff9a44d1cbeb807afadd72aee176f32c2381cf40e8140c37be4bb11b026ae02a7192df9e0adc52294ccdb57327fe66cfa8f978359349f32ccca931523834b86d84c168dfee41870e005dcd05815de71f53cc80285ba6a2d776bc87fb3d8b91655512437b671eb50840aeb21506ab85d0bd2651731634f14a91a40406cc69302621ee9a7b625c8236875ed769398d8d7f95cf2340b409f8424774274ce6ddde991ce43e0343e1aece361a08914512d91d68115d6da038fd883cc6545c0ebd6cade06cc0f577714f7df7254fe7f26f8dea1b36dcc05c674f3a929f6b2465716797fcd23473dd972353acd68d1f6e711ca36ecb959f5b78109126e80eca6879b5de6d2fc0dfcee0a6138a263768edec89aca336bacd0699f539e2eff5452778b482771714aa346f3ab740e4d62fdb91dbe30905088842fd8db37bf90dca2b3a16b5ed4ad723282d70f4a83c3b6e555c1d459a9bbee27ce96cd749f4b5da845ef08ce3d737a762c552a9cf04d88c414348c68c85a4ce4c26aa26283defadb8c2fefd5116c282ccb3c1a0bb61746d6d3b2d6c5b8414179edee5bb077c57c3bda6ca6336052dae3d0e4d23099a71b86d6bc682450106a88674efc62bace9592236abde56d30a8e68ea76db0eaf5bbe2962ad61bf4a058836e737a569790ac711720410369ee82c182b4a4424bfd02365872f8ac9ebf3d4f18e8c413b463dde3829e13d782e7570590571de5ddde92d7096c72275579a336e04fc9b52f24f5702f812a0a0a3ca2aac6b004ccd271708844293a9ea5fc65a254deb6742de38c4d4c3a302e1d0be698f52ac2bcd42e6f5f6605db495303813aa19d7dde48a2a42468be837ce926a67b02b393ee2db19905585a8792fcec863bafa4c1d55eca6e85c7f0f64861cd7395e98c646534a3bf9eb716561e0a5d797e896c922cde2940cd8ab0fc7cfae67a3b794c5c0e0d5a39ac5e9ae3ea9d8446856e8fbe365bc00b5f40f9687e10748d31ede5b465cc5d7bae7f6affac3395cd6cb29db199e1735e8c5f7e910b00157afb28f781f43f6f1201f4d5a37592b4f115fdae39bd09c06545079366b0faed26105aa4694f9b7bcdc5439f1d6ced97df2c15a6fef5cb7cfccc69060427811fa1db92bad8ec857bd1f954113ecd9359c17b3ac684e1cb1e74a50616ea3d0d87c5207143360fb53f2ae5589d09fd7d0f76e02e099fae412b0cfdec7fbdf5e9e99dfd9e0ab87b1517a0fb4022a69fac331df12b80b7211987263d57d2e9daa3500db97a248dfd6c3cfeea90e68c9da3967a4c09ecd12bcf5c1b5d48aa2516bc83f11e3a224f582e1f5ba4e2c4363dcd49e338c936c660a090dc3c16dfb2ce2402a509bd0c856f35ac861b55780bf776683050434884d2bf7ab8e9830d812116b2cd8c34d358c0205e5ceeb620dfca3ac7761d02d537777429bb01b9c437ce0f1cdf2f7c84290af8f02fcaab123ceee1b0ca0e87e6073601c2d4f4962de50a031680bb3c5c5c137455a9ceff526f49b3d5fd532ae21237ed5adf3afed1321bb17db561b118d119a3730ec9dc17ffb8edc28c50139c9b1635a776a2e9f035779da2d0b21fc5cfc2674d81ef391ef6bee8b0ff1e43e4f16e5d5d1a495be6c395a76f4f6afc1a304b5e16ce81c7e9e91a59b87bf31972a67fcbfccfa7208117d4e9774da54ea88c6f5d9dac8e6f3ac51cf411da0715fba949e91d0542c2aa9b71a45a41b21645bdab941fc133ef003bc232fae465656747fbe14ecc255bbd4b0b19760b0b9a7b10bebe67da88cd34112ffaa286db0a5461399645a45ce440a550d7e1ce1f220dd1c8b25e9e74e7b039146b36205acb5342ce57f3d5c8fa56561841433d6c3132aabc0ee34d1740da6814ec68e1fc5475df801e60818476f2091f35fc2e8b4131b625006f8f2906e299a8aa760fc43c9e882106f8914798fd482fe8e081d8d684b5906adb25ad6c6e112125dcf12cac090c17b82dd1d04b8275ac735726ce7b46d6b957562fc7b364c053747112631258316e6d28af2d64aa663fd77c65b05693fa7ec9ec7f1a58dddde1fdf4f10eeed4f0675d685450849fb464e771ea7449516deeeb19e11f799855193cf0432da44a4aad22167d7a6180350f6747f86a04737a1927f6fb730a636316741bd3fb219ea4e1e0ca3ff28a2699bb014d428f612effd684028b5d900018c90edf8bc946a7fb88b0bc28b4934214207be4db5dfcd6f0b48b1603671cd8eb8fb1c7f44d203fa2a65833abd3c36608dcf0bee3320fb6fa6af13d2e7a7bbd66e44db3b9f67877e9c58c883e7470ff4a134fcd5a578b3455504473b4bb9a93c02c6a1dffcafc0eac7d6628430c182d7feaa7ef6548052c91f9574129d27d8afc56ecd1596310d20df1c8e408a746f1a06779f121213755ec25635dc8af43a79f91b39009f91f7305a9681142f2d0ffcde6d7144f89b215b5e83e045973274a6ffd1dc1b01efb65023d38af0ad9e6d46f0207f5211f3792aaa24efa9f10d723edd742170b4d66b40aec4261801e53af5b4115c6fd2273d1b52dca62d7981e5dc7591f6df04d98184f081ab4b5b1089bc5a2bf0b490a6ea22b2a99e9c2da0e2ec64f35b3f0e8ada3a64a3d35e640c7b3d81666a64780f9d0ab738042d071a12c8b9682ced320edfa7598aea28f230a2112b034a2181da8114552cd8102e0fd64cacc655b5b0aba910690c80af0402517a38b91b72cc631a29b4c6e1d9ecd4e141d60ecd0a23dbeacd65bf4fe51c5005e87c28615fc53d22ffa62af1c834816ff151440dcf21f9af19f3141855569724bbf8eef7979a08247c6e689ad1e047a7cc0bb802fa5ae5df95ba261b335d1a2da55e8153ef167e2908fe14fcd6dbc383930855f61ca9961225410743b727dc705d6a7137556be420e2ef916a361c580a381227358e503df86357407dc8f9ed520d9905445b273c4dc87cbe0f4c9c718239f3a346aa74546c804b5e40543d904b557a7e1462989495c93e90b866fcb4a46c97637e6b65f37b7eaf80c870ed72bbce1fff8c2d87";
    std::string key_str = "YELLOW SUBMARINE";
    std::string expected_plaintext_str = "49276d206261636b20616e642049276d2072696e67696e27207468652062656c6c200a4120726f636b696e27206f6e20746865206d696b65207768696c652074686520666c79206769726c732079656c6c200a496e206563737461737920696e20746865206261636b206f66206d65200a57656c6c20746861742773206d7920444a204465736861792063757474696e2720616c6c207468656d205a2773200a48697474696e27206861726420616e6420746865206769726c69657320676f696e27206372617a79200a56616e696c6c612773206f6e20746865206d696b652c206d616e2049276d206e6f74206c617a792e200a0a49276d206c657474696e27206d792064727567206b69636b20696e200a497420636f6e74726f6c73206d79206d6f75746820616e64204920626567696e200a546f206a757374206c657420697420666c6f772c206c6574206d7920636f6e636570747320676f200a4d7920706f737365277320746f2074686520736964652079656c6c696e272c20476f2056616e696c6c6120476f21200a0a536d6f6f74682027636175736520746861742773207468652077617920492077696c6c206265200a416e6420696620796f7520646f6e2774206769766520612064616d6e2c207468656e200a57687920796f752073746172696e27206174206d65200a536f20676574206f666620276361757365204920636f6e74726f6c20746865207374616765200a54686572652773206e6f2064697373696e2720616c6c6f776564200a49276d20696e206d79206f776e207068617365200a546865206769726c69657320736120792074686579206c6f7665206d6520616e642074686174206973206f6b200a416e6420492063616e2064616e636520626574746572207468616e20616e79206b6964206e2720706c6179200a0a53746167652032202d2d2059656120746865206f6e65207961272077616e6e61206c697374656e20746f200a49742773206f6666206d79206865616420736f206c657420746865206265617420706c6179207468726f756768200a536f20492063616e2066756e6b20697420757020616e64206d616b6520697420736f756e6420676f6f64200a312d322d3320596f202d2d204b6e6f636b206f6e20736f6d6520776f6f64200a466f7220676f6f64206c75636b2c2049206c696b65206d79207268796d6573206174726f63696f7573200a537570657263616c6166726167696c697374696365787069616c69646f63696f7573200a49276d20616e2065666665637420616e64207468617420796f752063616e20626574200a492063616e2074616b65206120666c79206769726c20616e64206d616b6520686572207765742e200a0a49276d206c696b652053616d736f6e202d2d2053616d736f6e20746f2044656c696c6168200a54686572652773206e6f2064656e79696e272c20596f752063616e2074727920746f2068616e67200a42757420796f75276c6c206b65657020747279696e2720746f20676574206d79207374796c65200a4f76657220616e64206f7665722c207072616374696365206d616b65732070657266656374200a427574206e6f7420696620796f752772652061206c6f616665722e200a0a596f75276c6c20676574206e6f77686572652c206e6f20706c6163652c206e6f2074696d652c206e6f206769726c73200a536f6f6e202d2d204f68206d7920476f642c20686f6d65626f64792c20796f752070726f6261626c7920656174200a537061676865747469207769746820612073706f6f6e2120436f6d65206f6e20616e642073617920697421200a0a5649502e2056616e696c6c6120496365207965702c207965702c2049276d20636f6d696e272068617264206c696b652061207268696e6f200a496e746f7869636174696e6720736f20796f752073746167676572206c696b6520612077696e6f200a536f2070756e6b732073746f7020747279696e6720616e64206769726c2073746f7020637279696e27200a56616e696c6c61204963652069732073656c6c696e2720616e6420796f752070656f706c652061726520627579696e27200a274361757365207768792074686520667265616b7320617265206a6f636b696e27206c696b65204372617a7920476c7565200a4d6f76696e2720616e642067726f6f76696e2720747279696e6720746f2073696e6720616c6f6e67200a416c6c207468726f756768207468652067686574746f2067726f6f76696e272074686973206865726520736f6e67200a4e6f7720796f7527726520616d617a6564206279207468652056495020706f7373652e200a0a5374657070696e2720736f2068617264206c696b652061204765726d616e204e617a69200a53746172746c6564206279207468652062617365732068697474696e272067726f756e64200a54686572652773206e6f207472697070696e27206f6e206d696e652c2049276d206a7573742067657474696e2720646f776e200a537061726b616d617469632c2049276d2068616e67696e27207469676874206c696b6520612066616e61746963200a596f752074726170706564206d65206f6e636520616e6420492074686f756768742074686174200a596f75206d696768742068617665206974200a536f207374657020646f776e20616e64206c656e64206d6520796f757220656172200a27383920696e206d792074696d652120596f752c20273930206973206d7920796561722e200a0a596f75277265207765616b656e696e2720666173742c20594f2120616e6420492063616e2074656c6c206974200a596f757220626f647927732067657474696e2720686f742c20736f2c20736f20492063616e20736d656c6c206974200a536f20646f6e2774206265206d616420616e6420646f6e277420626520736164200a27436175736520746865206c79726963732062656c6f6e6720746f204943452c20596f752063616e2063616c6c206d6520446164200a596f75277265207069746368696e272061206669742c20736f2073746570206261636b20616e6420656e64757265200a4c65742074686520776974636820646f63746f722c204963652c20646f207468652064616e636520746f2063757265200a536f20636f6d6520757020636c6f736520616e6420646f6e277420626520737175617265200a596f752077616e6e6120626174746c65206d65202d2d20416e7974696d652c20616e797768657265200a0a596f752074686f756768742074686174204920776173207765616b2c20426f792c20796f7527726520646561642077726f6e67200a536f20636f6d65206f6e2c206576657279626f647920616e642073696e67207468697320736f6e67200a0a536179202d2d20506c617920746861742066756e6b79206d75736963205361792c20676f20776869746520626f792c20676f20776869746520626f7920676f200a706c617920746861742066756e6b79206d7573696320476f20776869746520626f792c20676f20776869746520626f792c20676f200a4c617920646f776e20616e6420626f6f67696520616e6420706c617920746861742066756e6b79206d757369632074696c6c20796f75206469652e200a0a506c617920746861742066756e6b79206d7573696320436f6d65206f6e2c20436f6d65206f6e2c206c6574206d652068656172200a506c617920746861742066756e6b79206d7573696320776869746520626f7920796f75207361792069742c20736179206974200a506c617920746861742066756e6b79206d757369632041206c6974746c65206c6f75646572206e6f77200a506c617920746861742066756e6b79206d757369632c20776869746520626f7920436f6d65206f6e2c20436f6d65206f6e2c20436f6d65206f6e200a506c617920746861742066756e6b79206d75736963200a04040404";

    std::vector<byte> ciphertext_data = base_string_conversions::hex_to_bytes(ciphertext_str);
    std::vector<byte> key(key_str.begin(), key_str.end());
    std::vector<byte> plaintext_data = crypto_utils::aes_ecb_decrypt(ciphertext_data, key, 128);
    std::string plaintext_hex = base_string_conversions::bytes_to_hex(plaintext_data);
    EXPECT_EQ(plaintext_hex, expected_plaintext_str);
}

TEST(CryptoUtils, aes_ecb_encrypt)
{
    std::string plaintext_str = "49276d206261636b20616e642049276d2072696e67696e27207468652062656c6c200a4120726f636b696e27206f6e20746865206d696b65207768696c652074686520666c79206769726c732079656c6c200a496e206563737461737920696e20746865206261636b206f66206d65200a57656c6c20746861742773206d7920444a204465736861792063757474696e2720616c6c207468656d205a2773200a48697474696e27206861726420616e6420746865206769726c69657320676f696e27206372617a79200a56616e696c6c612773206f6e20746865206d696b652c206d616e2049276d206e6f74206c617a792e200a0a49276d206c657474696e27206d792064727567206b69636b20696e200a497420636f6e74726f6c73206d79206d6f75746820616e64204920626567696e200a546f206a757374206c657420697420666c6f772c206c6574206d7920636f6e636570747320676f200a4d7920706f737365277320746f2074686520736964652079656c6c696e272c20476f2056616e696c6c6120476f21200a0a536d6f6f74682027636175736520746861742773207468652077617920492077696c6c206265200a416e6420696620796f7520646f6e2774206769766520612064616d6e2c207468656e200a57687920796f752073746172696e27206174206d65200a536f20676574206f666620276361757365204920636f6e74726f6c20746865207374616765200a54686572652773206e6f2064697373696e2720616c6c6f776564200a49276d20696e206d79206f776e207068617365200a546865206769726c69657320736120792074686579206c6f7665206d6520616e642074686174206973206f6b200a416e6420492063616e2064616e636520626574746572207468616e20616e79206b6964206e2720706c6179200a0a53746167652032202d2d2059656120746865206f6e65207961272077616e6e61206c697374656e20746f200a49742773206f6666206d79206865616420736f206c657420746865206265617420706c6179207468726f756768200a536f20492063616e2066756e6b20697420757020616e64206d616b6520697420736f756e6420676f6f64200a312d322d3320596f202d2d204b6e6f636b206f6e20736f6d6520776f6f64200a466f7220676f6f64206c75636b2c2049206c696b65206d79207268796d6573206174726f63696f7573200a537570657263616c6166726167696c697374696365787069616c69646f63696f7573200a49276d20616e2065666665637420616e64207468617420796f752063616e20626574200a492063616e2074616b65206120666c79206769726c20616e64206d616b6520686572207765742e200a0a49276d206c696b652053616d736f6e202d2d2053616d736f6e20746f2044656c696c6168200a54686572652773206e6f2064656e79696e272c20596f752063616e2074727920746f2068616e67200a42757420796f75276c6c206b65657020747279696e2720746f20676574206d79207374796c65200a4f76657220616e64206f7665722c207072616374696365206d616b65732070657266656374200a427574206e6f7420696620796f752772652061206c6f616665722e200a0a596f75276c6c20676574206e6f77686572652c206e6f20706c6163652c206e6f2074696d652c206e6f206769726c73200a536f6f6e202d2d204f68206d7920476f642c20686f6d65626f64792c20796f752070726f6261626c7920656174200a537061676865747469207769746820612073706f6f6e2120436f6d65206f6e20616e642073617920697421200a0a5649502e2056616e696c6c6120496365207965702c207965702c2049276d20636f6d696e272068617264206c696b652061207268696e6f200a496e746f7869636174696e6720736f20796f752073746167676572206c696b6520612077696e6f200a536f2070756e6b732073746f7020747279696e6720616e64206769726c2073746f7020637279696e27200a56616e696c6c61204963652069732073656c6c696e2720616e6420796f752070656f706c652061726520627579696e27200a274361757365207768792074686520667265616b7320617265206a6f636b696e27206c696b65204372617a7920476c7565200a4d6f76696e2720616e642067726f6f76696e2720747279696e6720746f2073696e6720616c6f6e67200a416c6c207468726f756768207468652067686574746f2067726f6f76696e272074686973206865726520736f6e67200a4e6f7720796f7527726520616d617a6564206279207468652056495020706f7373652e200a0a5374657070696e2720736f2068617264206c696b652061204765726d616e204e617a69200a53746172746c6564206279207468652062617365732068697474696e272067726f756e64200a54686572652773206e6f207472697070696e27206f6e206d696e652c2049276d206a7573742067657474696e2720646f776e200a537061726b616d617469632c2049276d2068616e67696e27207469676874206c696b6520612066616e61746963200a596f752074726170706564206d65206f6e636520616e6420492074686f756768742074686174200a596f75206d696768742068617665206974200a536f207374657020646f776e20616e64206c656e64206d6520796f757220656172200a27383920696e206d792074696d652120596f752c20273930206973206d7920796561722e200a0a596f75277265207765616b656e696e2720666173742c20594f2120616e6420492063616e2074656c6c206974200a596f757220626f647927732067657474696e2720686f742c20736f2c20736f20492063616e20736d656c6c206974200a536f20646f6e2774206265206d616420616e6420646f6e277420626520736164200a27436175736520746865206c79726963732062656c6f6e6720746f204943452c20596f752063616e2063616c6c206d6520446164200a596f75277265207069746368696e272061206669742c20736f2073746570206261636b20616e6420656e64757265200a4c65742074686520776974636820646f63746f722c204963652c20646f207468652064616e636520746f2063757265200a536f20636f6d6520757020636c6f736520616e6420646f6e277420626520737175617265200a596f752077616e6e6120626174746c65206d65202d2d20416e7974696d652c20616e797768657265200a0a596f752074686f756768742074686174204920776173207765616b2c20426f792c20796f7527726520646561642077726f6e67200a536f20636f6d65206f6e2c206576657279626f647920616e642073696e67207468697320736f6e67200a0a536179202d2d20506c617920746861742066756e6b79206d75736963205361792c20676f20776869746520626f792c20676f20776869746520626f7920676f200a706c617920746861742066756e6b79206d7573696320476f20776869746520626f792c20676f20776869746520626f792c20676f200a4c617920646f776e20616e6420626f6f67696520616e6420706c617920746861742066756e6b79206d757369632074696c6c20796f75206469652e200a0a506c617920746861742066756e6b79206d7573696320436f6d65206f6e2c20436f6d65206f6e2c206c6574206d652068656172200a506c617920746861742066756e6b79206d7573696320776869746520626f7920796f75207361792069742c20736179206974200a506c617920746861742066756e6b79206d757369632041206c6974746c65206c6f75646572206e6f77200a506c617920746861742066756e6b79206d757369632c20776869746520626f7920436f6d65206f6e2c20436f6d65206f6e2c20436f6d65206f6e200a506c617920746861742066756e6b79206d75736963200a04040404";
    std::string key_str = "YELLOW SUBMARINE";
    std::string expected_ciphertext_str = "091230aade3eb330dbaa4358f88d2a6c37b72d0cf4c22c344aec4142d00ce530dd31b8c2303fef7a75035bd04b3c45ce0db93a6b8f2831b018e830d9b2e2db734b91f5ca7d850d10406013cb20844aad8d4acbe1c79cca94bb7376c9df2b9103e6caca8caec5cf8437f3fb6d77eb2d2fff569c3ce526f028ed606c8c8e5825cda098061ac8d7e6096da585913f64b1b40810f668fc345b8d7b4186f870020e5bdda3611889e0f4ec0411c37bca38270a9a51a73aaea762f37de46f200e57f63644c6cdd280dbf51abcb911ef6eba9025a26279ab3012d324814b773f94ed81e87b27e844e93474b87a2df16cc7c8028d6d4587a22ff9cdc442522a6f54e60ba0165794dbb8aa7c28099452060bc2c13773dc26eca7f3f6c1707cb62cfa97dacbd9b2e106dd77431ca186ed07d3e24a8fab2849e5f9643d51a62969f67711d6d1d6f3ebaead02b25cde3129e1a368a2ce7a3af6c43230f9a585ec6b33538a898570675d321450d51f465c04a52e8565cb0ccde990177d1ecd22477e95bb0d51f3c222f27a24c944aa15530a38dcf5eea672570e6532b026b69d0cff884c32a2bea43de90bbf572c9b53dad8b6666c0f548f3cfccdbfe0157b50a8100de3303cff0b7455fa0eb0467072c68b39650fb45fd1cb756194ac1713b8061ff6db4a1008290a8caaa52412e719dc73c7015a7b6429f73b1ebe739409dd4bfc57b2fb4a9ae87cf14de85fa47c3338cc0739f5da39b70803a029426f1c46d0bd7d4c11878983f70b281e6351cb32b5fa2aaca925f1495b93bdc0d205d2a7ce0b6956160c1ac8ec2ae35c5d152096d3f10149cedc270dcdd3a59386b5b92e29803ade4bf5cec8938608c6ed0af496700317dc5384a162ee9eb989962cff7cfaabd19c8ad791e3ee812f5348e24e1f3294a0e71bd7f29877d35914711ca79f037faad7162cfd0d2abcd2b47929fb3e33e56eab967acd8f7cfd23f403a51122bf4d16ef82b3dfe07feab84d1c2c3b344c8cc43324bf1fed35cf1071f6faa11ca432b3ff9a44d1cbeb807afadd72aee176f32c2381cf40e8140c37be4bb11b026ae02a7192df9e0adc52294ccdb57327fe66cfa8f978359349f32ccca931523834b86d84c168dfee41870e005dcd05815de71f53cc80285ba6a2d776bc87fb3d8b91655512437b671eb50840aeb21506ab85d0bd2651731634f14a91a40406cc69302621ee9a7b625c8236875ed769398d8d7f95cf2340b409f8424774274ce6ddde991ce43e0343e1aece361a08914512d91d68115d6da038fd883cc6545c0ebd6cade06cc0f577714f7df7254fe7f26f8dea1b36dcc05c674f3a929f6b2465716797fcd23473dd972353acd68d1f6e711ca36ecb959f5b78109126e80eca6879b5de6d2fc0dfcee0a6138a263768edec89aca336bacd0699f539e2eff5452778b482771714aa346f3ab740e4d62fdb91dbe30905088842fd8db37bf90dca2b3a16b5ed4ad723282d70f4a83c3b6e555c1d459a9bbee27ce96cd749f4b5da845ef08ce3d737a762c552a9cf04d88c414348c68c85a4ce4c26aa26283defadb8c2fefd5116c282ccb3c1a0bb61746d6d3b2d6c5b8414179edee5bb077c57c3bda6ca6336052dae3d0e4d23099a71b86d6bc682450106a88674efc62bace9592236abde56d30a8e68ea76db0eaf5bbe2962ad61bf4a058836e737a569790ac711720410369ee82c182b4a4424bfd02365872f8ac9ebf3d4f18e8c413b463dde3829e13d782e7570590571de5ddde92d7096c72275579a336e04fc9b52f24f5702f812a0a0a3ca2aac6b004ccd271708844293a9ea5fc65a254deb6742de38c4d4c3a302e1d0be698f52ac2bcd42e6f5f6605db495303813aa19d7dde48a2a42468be837ce926a67b02b393ee2db19905585a8792fcec863bafa4c1d55eca6e85c7f0f64861cd7395e98c646534a3bf9eb716561e0a5d797e896c922cde2940cd8ab0fc7cfae67a3b794c5c0e0d5a39ac5e9ae3ea9d8446856e8fbe365bc00b5f40f9687e10748d31ede5b465cc5d7bae7f6affac3395cd6cb29db199e1735e8c5f7e910b00157afb28f781f43f6f1201f4d5a37592b4f115fdae39bd09c06545079366b0faed26105aa4694f9b7bcdc5439f1d6ced97df2c15a6fef5cb7cfccc69060427811fa1db92bad8ec857bd1f954113ecd9359c17b3ac684e1cb1e74a50616ea3d0d87c5207143360fb53f2ae5589d09fd7d0f76e02e099fae412b0cfdec7fbdf5e9e99dfd9e0ab87b1517a0fb4022a69fac331df12b80b7211987263d57d2e9daa3500db97a248dfd6c3cfeea90e68c9da3967a4c09ecd12bcf5c1b5d48aa2516bc83f11e3a224f582e1f5ba4e2c4363dcd49e338c936c660a090dc3c16dfb2ce2402a509bd0c856f35ac861b55780bf776683050434884d2bf7ab8e9830d812116b2cd8c34d358c0205e5ceeb620dfca3ac7761d02d537777429bb01b9c437ce0f1cdf2f7c84290af8f02fcaab123ceee1b0ca0e87e6073601c2d4f4962de50a031680bb3c5c5c137455a9ceff526f49b3d5fd532ae21237ed5adf3afed1321bb17db561b118d119a3730ec9dc17ffb8edc28c50139c9b1635a776a2e9f035779da2d0b21fc5cfc2674d81ef391ef6bee8b0ff1e43e4f16e5d5d1a495be6c395a76f4f6afc1a304b5e16ce81c7e9e91a59b87bf31972a67fcbfccfa7208117d4e9774da54ea88c6f5d9dac8e6f3ac51cf411da0715fba949e91d0542c2aa9b71a45a41b21645bdab941fc133ef003bc232fae465656747fbe14ecc255bbd4b0b19760b0b9a7b10bebe67da88cd34112ffaa286db0a5461399645a45ce440a550d7e1ce1f220dd1c8b25e9e74e7b039146b36205acb5342ce57f3d5c8fa56561841433d6c3132aabc0ee34d1740da6814ec68e1fc5475df801e60818476f2091f35fc2e8b4131b625006f8f2906e299a8aa760fc43c9e882106f8914798fd482fe8e081d8d684b5906adb25ad6c6e112125dcf12cac090c17b82dd1d04b8275ac735726ce7b46d6b957562fc7b364c053747112631258316e6d28af2d64aa663fd77c65b05693fa7ec9ec7f1a58dddde1fdf4f10eeed4f0675d685450849fb464e771ea7449516deeeb19e11f799855193cf0432da44a4aad22167d7a6180350f6747f86a04737a1927f6fb730a636316741bd3fb219ea4e1e0ca3ff28a2699bb014d428f612effd684028b5d900018c90edf8bc946a7fb88b0bc28b4934214207be4db5dfcd6f0b48b1603671cd8eb8fb1c7f44d203fa2a65833abd3c36608dcf0bee3320fb6fa6af13d2e7a7bbd66e44db3b9f67877e9c58c883e7470ff4a134fcd5a578b3455504473b4bb9a93c02c6a1dffcafc0eac7d6628430c182d7feaa7ef6548052c91f9574129d27d8afc56ecd1596310d20df1c8e408a746f1a06779f121213755ec25635dc8af43a79f91b39009f91f7305a9681142f2d0ffcde6d7144f89b215b5e83e045973274a6ffd1dc1b01efb65023d38af0ad9e6d46f0207f5211f3792aaa24efa9f10d723edd742170b4d66b40aec4261801e53af5b4115c6fd2273d1b52dca62d7981e5dc7591f6df04d98184f081ab4b5b1089bc5a2bf0b490a6ea22b2a99e9c2da0e2ec64f35b3f0e8ada3a64a3d35e640c7b3d81666a64780f9d0ab738042d071a12c8b9682ced320edfa7598aea28f230a2112b034a2181da8114552cd8102e0fd64cacc655b5b0aba910690c80af0402517a38b91b72cc631a29b4c6e1d9ecd4e141d60ecd0a23dbeacd65bf4fe51c5005e87c28615fc53d22ffa62af1c834816ff151440dcf21f9af19f3141855569724bbf8eef7979a08247c6e689ad1e047a7cc0bb802fa5ae5df95ba261b335d1a2da55e8153ef167e2908fe14fcd6dbc383930855f61ca9961225410743b727dc705d6a7137556be420e2ef916a361c580a381227358e503df86357407dc8f9ed520d9905445b273c4dc87cbe0f4c9c718239f3a346aa74546c804b5e40543d904b557a7e1462989495c93e90b866fcb4a46c97637e6b65f37b7eaf80c870ed72bbce1fff8c2d87";

    std::vector<byte> plaintext_data = base_string_conversions::hex_to_bytes(plaintext_str);
    std::vector<byte> key(key_str.begin(), key_str.end());
    std::vector<byte> ciphertext_data = crypto_utils::aes_ecb_encrypt(plaintext_data, key, 128);
    std::string ciphertext_hex = base_string_conversions::bytes_to_hex(ciphertext_data);
    EXPECT_EQ(ciphertext_hex, expected_ciphertext_str);
}
