const hello = require('./build/Release/rfcnative.node');


const uids = ["0", "1", "350350353", "002141242"];

const stressful1 = [...uids, ...uids, ...uids, ...uids];

console.log(hello.process_op8({
    discord_members: [{
        id: "0",
        nickname: "test",
        user: {
            id: "0",
            username: "test",
            discriminator: "1",
            premium_since: new Date().toISOString(),
        }
    }],
    user_ids: [...stressful1, ...stressful1, ...stressful1],
}));