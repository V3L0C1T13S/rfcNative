const rfcNative = require('./index.js');


const uids = ["0", "1", "350350353", "002141242"];

const stressful1 = [...uids, ...uids, ...uids, ...uids];

console.log(rfcNative.processOP8({
    discord_members: [{
        id: "0",
        nickname: "test",
        user: {
            id: "0",
            username: "test",
            discriminator: "1",
            premium_since: new Date().toISOString(),
        }
    }, {
        id: "1",
        nickname: "amogus",
        user: {
            id: "1",
            username: "amogus",
            discriminator: "1",
            premium_since: new Date().toISOString(),
        }
    }],
    user_ids: uids,
    presences: false,
    query: "amog",
}));