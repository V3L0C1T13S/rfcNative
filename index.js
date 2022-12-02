const rfcNative = require("./build/Release/rfcnative.node");

export function processOP8(data) {
    return rfcNative.process_op8(data);
}
