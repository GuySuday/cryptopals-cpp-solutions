#include <gtest/gtest.h>
#include <string> // std::string

#include "sets/01_basics/07_aes_in_ecb_mode.hpp"
#include "utils/base_string_conversions.hpp"
#include "utils/file_utils.hpp"
#include "utils/crypto_utils.hpp"
#include "utils/types.hpp" // byte

TEST(DecryptAesEcb, cryptopals_example)
{
    std::string encoded_data_file_path = "resources/set1_challenge7.txt";
    std::string key_str = "YELLOW SUBMARINE";
    std::string expected_plaintext_hex = "49276d206261636b20616e642049276d2072696e67696e27207468652062656c6c200a4120726f636b696e27206f6e20746865206d696b65207768696c652074686520666c79206769726c732079656c6c200a496e206563737461737920696e20746865206261636b206f66206d65200a57656c6c20746861742773206d7920444a204465736861792063757474696e2720616c6c207468656d205a2773200a48697474696e27206861726420616e6420746865206769726c69657320676f696e27206372617a79200a56616e696c6c612773206f6e20746865206d696b652c206d616e2049276d206e6f74206c617a792e200a0a49276d206c657474696e27206d792064727567206b69636b20696e200a497420636f6e74726f6c73206d79206d6f75746820616e64204920626567696e200a546f206a757374206c657420697420666c6f772c206c6574206d7920636f6e636570747320676f200a4d7920706f737365277320746f2074686520736964652079656c6c696e272c20476f2056616e696c6c6120476f21200a0a536d6f6f74682027636175736520746861742773207468652077617920492077696c6c206265200a416e6420696620796f7520646f6e2774206769766520612064616d6e2c207468656e200a57687920796f752073746172696e27206174206d65200a536f20676574206f666620276361757365204920636f6e74726f6c20746865207374616765200a54686572652773206e6f2064697373696e2720616c6c6f776564200a49276d20696e206d79206f776e207068617365200a546865206769726c69657320736120792074686579206c6f7665206d6520616e642074686174206973206f6b200a416e6420492063616e2064616e636520626574746572207468616e20616e79206b6964206e2720706c6179200a0a53746167652032202d2d2059656120746865206f6e65207961272077616e6e61206c697374656e20746f200a49742773206f6666206d79206865616420736f206c657420746865206265617420706c6179207468726f756768200a536f20492063616e2066756e6b20697420757020616e64206d616b6520697420736f756e6420676f6f64200a312d322d3320596f202d2d204b6e6f636b206f6e20736f6d6520776f6f64200a466f7220676f6f64206c75636b2c2049206c696b65206d79207268796d6573206174726f63696f7573200a537570657263616c6166726167696c697374696365787069616c69646f63696f7573200a49276d20616e2065666665637420616e64207468617420796f752063616e20626574200a492063616e2074616b65206120666c79206769726c20616e64206d616b6520686572207765742e200a0a49276d206c696b652053616d736f6e202d2d2053616d736f6e20746f2044656c696c6168200a54686572652773206e6f2064656e79696e272c20596f752063616e2074727920746f2068616e67200a42757420796f75276c6c206b65657020747279696e2720746f20676574206d79207374796c65200a4f76657220616e64206f7665722c207072616374696365206d616b65732070657266656374200a427574206e6f7420696620796f752772652061206c6f616665722e200a0a596f75276c6c20676574206e6f77686572652c206e6f20706c6163652c206e6f2074696d652c206e6f206769726c73200a536f6f6e202d2d204f68206d7920476f642c20686f6d65626f64792c20796f752070726f6261626c7920656174200a537061676865747469207769746820612073706f6f6e2120436f6d65206f6e20616e642073617920697421200a0a5649502e2056616e696c6c6120496365207965702c207965702c2049276d20636f6d696e272068617264206c696b652061207268696e6f200a496e746f7869636174696e6720736f20796f752073746167676572206c696b6520612077696e6f200a536f2070756e6b732073746f7020747279696e6720616e64206769726c2073746f7020637279696e27200a56616e696c6c61204963652069732073656c6c696e2720616e6420796f752070656f706c652061726520627579696e27200a274361757365207768792074686520667265616b7320617265206a6f636b696e27206c696b65204372617a7920476c7565200a4d6f76696e2720616e642067726f6f76696e2720747279696e6720746f2073696e6720616c6f6e67200a416c6c207468726f756768207468652067686574746f2067726f6f76696e272074686973206865726520736f6e67200a4e6f7720796f7527726520616d617a6564206279207468652056495020706f7373652e200a0a5374657070696e2720736f2068617264206c696b652061204765726d616e204e617a69200a53746172746c6564206279207468652062617365732068697474696e272067726f756e64200a54686572652773206e6f207472697070696e27206f6e206d696e652c2049276d206a7573742067657474696e2720646f776e200a537061726b616d617469632c2049276d2068616e67696e27207469676874206c696b6520612066616e61746963200a596f752074726170706564206d65206f6e636520616e6420492074686f756768742074686174200a596f75206d696768742068617665206974200a536f207374657020646f776e20616e64206c656e64206d6520796f757220656172200a27383920696e206d792074696d652120596f752c20273930206973206d7920796561722e200a0a596f75277265207765616b656e696e2720666173742c20594f2120616e6420492063616e2074656c6c206974200a596f757220626f647927732067657474696e2720686f742c20736f2c20736f20492063616e20736d656c6c206974200a536f20646f6e2774206265206d616420616e6420646f6e277420626520736164200a27436175736520746865206c79726963732062656c6f6e6720746f204943452c20596f752063616e2063616c6c206d6520446164200a596f75277265207069746368696e272061206669742c20736f2073746570206261636b20616e6420656e64757265200a4c65742074686520776974636820646f63746f722c204963652c20646f207468652064616e636520746f2063757265200a536f20636f6d6520757020636c6f736520616e6420646f6e277420626520737175617265200a596f752077616e6e6120626174746c65206d65202d2d20416e7974696d652c20616e797768657265200a0a596f752074686f756768742074686174204920776173207765616b2c20426f792c20796f7527726520646561642077726f6e67200a536f20636f6d65206f6e2c206576657279626f647920616e642073696e67207468697320736f6e67200a0a536179202d2d20506c617920746861742066756e6b79206d75736963205361792c20676f20776869746520626f792c20676f20776869746520626f7920676f200a706c617920746861742066756e6b79206d7573696320476f20776869746520626f792c20676f20776869746520626f792c20676f200a4c617920646f776e20616e6420626f6f67696520616e6420706c617920746861742066756e6b79206d757369632074696c6c20796f75206469652e200a0a506c617920746861742066756e6b79206d7573696320436f6d65206f6e2c20436f6d65206f6e2c206c6574206d652068656172200a506c617920746861742066756e6b79206d7573696320776869746520626f7920796f75207361792069742c20736179206974200a506c617920746861742066756e6b79206d757369632041206c6974746c65206c6f75646572206e6f77200a506c617920746861742066756e6b79206d757369632c20776869746520626f7920436f6d65206f6e2c20436f6d65206f6e2c20436f6d65206f6e200a506c617920746861742066756e6b79206d75736963200a04040404";

    std::string encoded_ciphertext_str = file_utils::read_file_without_newlines(encoded_data_file_path);
    std::vector<byte> encoded_ciphertext(encoded_ciphertext_str.begin(), encoded_ciphertext_str.end());
    std::vector<byte> key(key_str.begin(), key_str.end());
    std::string plaintext_hex = s01::c07::decrypt_aes_128_ecb(encoded_ciphertext, key);

    EXPECT_EQ(plaintext_hex, expected_plaintext_hex);

    std::vector<byte> plaintext_data = base_string_conversions::hex_to_bytes(plaintext_hex);
    std::vector<byte> decryped_data = crypto_utils::aes_ecb_encrypt(plaintext_data, key, 128);
    std::string decryped_data_hex = base_string_conversions::bytes_to_hex(decryped_data);
    std::string encoded_decrypted_str = base_string_conversions::hex_to_base64(decryped_data_hex);

    EXPECT_EQ(encoded_decrypted_str, encoded_ciphertext_str);
}