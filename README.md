# QmlJson
QmlJson component for QtQuick applications.

## Build

```
qmake
make
make install
```

## Installation

Copy in your qml import path the folder `QmlJson` inside `plugins` or add to your
import path `plugins`.

## Example

```qml
import QtQuick 2.8
import QtQuick.Window 2.2
import QmlJson 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    QmlJson {
        id: posts
        source: "https://jsonplaceholder.typicode.com/posts"
        interval: 2000
        polling: true
        onDataChanged: console.log("RELOAD")
    }

    ListView {
        anchors.fill: parent
        model: posts.data
        delegate: Text {
            text: modelData.title
        }
    }
}

```
