//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

using ::testing::Return;

TEST_F(WeatherTestCase, SetApiKey) {
    ::testing::StrictMock<WeatherMock> weather;

    ASSERT_NO_THROW(weather.SetApiKey("my_api_key"));
}

TEST_F(WeatherTestCase, GetResponseForCity) {
    ::testing::StrictMock<WeatherMock> weather;

    cpr::Response r;
    r.status_code = 200;
    r.text = "{\"list\": [{\"main\": {\"temp\": 20.3}}]}";
    EXPECT_CALL(weather, Get("Moscow")).WillOnce(Return(r));

    ASSERT_EQ(weather.GetResponseForCity("Moscow"), json::parse("{\"list\": [{\"main\": {\"temp\": 20.3}}]}"));
}

TEST_F(WeatherTestCase, GetResponseForCityNotFound) {
    ::testing::StrictMock<WeatherMock> weather;

    cpr::Response r;
    r.status_code = 202;
    r.text = "{\"list\": [{\"main\": {\"temp\": 20.3}}]}";
    EXPECT_CALL(weather, Get("Moscow")).WillOnce(Return(r));

    ASSERT_THROW(weather.GetResponseForCity("Moscow"), std::invalid_argument);
}

TEST_F(WeatherTestCase, GetTemperature) {
    ::testing::StrictMock<WeatherMock> weather;

    cpr::Response r;
    r.status_code = 200;
    r.text = "{\"list\": [{\"main\": {\"temp\": 20.3}}]}";
    EXPECT_CALL(weather, Get("Moscow")).WillOnce(Return(r));

    ASSERT_FLOAT_EQ(weather.GetTemperature("Moscow"), 20.3);
}

TEST_F(WeatherTestCase, FindDiffBetweenTwoCities) {
    ::testing::StrictMock<WeatherMock> weather;

    cpr::Response r1;
    r1.status_code = 200;
    r1.text = "{\"list\": [{\"main\": {\"temp\": 20.3}}]}";
    EXPECT_CALL(weather, Get("Moscow")).WillOnce(Return(r1));

    cpr::Response r2;
    r2.status_code = 200;
    r2.text = "{\"list\": [{\"main\": {\"temp\": 10}}]}";
    EXPECT_CALL(weather, Get("Saint-Petersburg")).WillOnce(Return(r2));

    ASSERT_FLOAT_EQ(weather.FindDiffBetweenTwoCities("Moscow", "Saint-Petersburg"), 10.3);
}

TEST_F(WeatherTestCase, GetDifferenceStringWarmer) {
    ::testing::StrictMock<WeatherMock> weather;

    cpr::Response r1;
    r1.status_code = 200;
    r1.text = "{\"list\": [{\"main\": {\"temp\": 20.3}}]}";
    EXPECT_CALL(weather, Get("Moscow")).WillOnce(Return(r1));

    cpr::Response r2;
    r2.status_code = 200;
    r2.text = "{\"list\": [{\"main\": {\"temp\": 10}}]}";
    EXPECT_CALL(weather, Get("Saint-Petersburg")).WillOnce(Return(r2));

    ASSERT_EQ(weather.GetDifferenceString("Moscow", "Saint-Petersburg"),
              "Weather in Moscow is warmer than in Saint-Petersburg by 10 degrees");
}

TEST_F(WeatherTestCase, GetDifferenceStringColder) {
    ::testing::StrictMock<WeatherMock> weather;

    cpr::Response r1;
    r1.status_code = 200;
    r1.text = "{\"list\": [{\"main\": {\"temp\": 20.3}}]}";
    EXPECT_CALL(weather, Get("Saint-Petersburg")).WillOnce(Return(r1));

    cpr::Response r2;
    r2.status_code = 200;
    r2.text = "{\"list\": [{\"main\": {\"temp\": 10}}]}";
    EXPECT_CALL(weather, Get("Moscow")).WillOnce(Return(r2));

    ASSERT_EQ(weather.GetDifferenceString("Moscow", "Saint-Petersburg"),
              "Weather in Moscow is colder than in Saint-Petersburg by 10 degrees");
}
