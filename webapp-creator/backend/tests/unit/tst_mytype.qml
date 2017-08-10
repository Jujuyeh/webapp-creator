import QtQuick 2.4
import QtTest 1.0
import Ubuntu.Components 1.3
import Webapp_Creator 1.0

// See more details @ http://qt-project.org/doc/qt-5.0/qtquick/qml-testcase.html

// Execute tests with:
//   qmltestrunner

Item {
    // The objects
    MyType {
        id: objectUnderTest
    }

    TestCase {
        name: "MyType"

        function init() {
            console.debug(">> init");
            compare("",objectUnderTest.helloWorld,"text was not empty on init");
            console.debug("<< init");
        }

        function cleanup() {
            console.debug(">> cleanup");
            console.debug("<< cleanup");
        }

        function initTestCase() {
            console.debug(">> initTestCase");
            console.debug("<< initTestCase");
        }

        function cleanupTestCase() {
            console.debug(">> cleanupTestCase");
            console.debug("<< cleanupTestCase");
        }

        function test_canReadAndWriteText() {
            var expected = "Hello World 2";

            objectUnderTest.helloWorld = expected;

            compare(expected,objectUnderTest.helloWorld,"expected did not equal result");
        }
    }
}
