const rfcNative = require("./build/Release/rfcnative.node");

module.exports.processOP8 = function (data) {
    return rfcNative.process_op8(data);
}