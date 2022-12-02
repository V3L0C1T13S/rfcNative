#include <napi.h>
#include <map>

struct GuildMembersChunk
{
    Napi::Array guild_id;
    Napi::Array members;
    Napi::Array not_found;
    Napi::Array presences;
};

struct GuildMemberArgs
{
    Napi::Array discord_members;
    Napi::Array user_ids;
    Napi::Boolean presences;
};

Napi::Object ProcessOP8(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();
        return Napi::Object::New(env);
    }

    if (!info[0].IsObject())
    {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return Napi::Object::New(env);
    }

    Napi::Object member_info = info[0].As<Napi::Object>();
    Napi::Array members = member_info.Get("discord_members").As<Napi::Array>();
    Napi::Array users = member_info.Get("user_ids").As<Napi::Array>();

    Napi::Array guild_id = Napi::Array::New(env);
    Napi::Array discord_members = Napi::Array::New(env);
    Napi::Array not_found = Napi::Array::New(env);
    Napi::Array presences = Napi::Array::New(env);

    std::map<std::string, Napi::Object> members_by_id;

    for (uint32_t i = 0; i < members.Length(); i++)
    {
        auto member = members.Get(i).As<Napi::Object>();
        auto id = member.Get("id").As<Napi::String>().Utf8Value();

        members_by_id.insert(std::pair<std::string, Napi::Object>(id, member));
    }

    Napi::Object result_body = Napi::Object::New(env);
    result_body.Set("guild_id", guild_id);
    result_body.Set("members", discord_members);
    result_body.Set("not_found", not_found);
    result_body.Set("presences", presences);

    for (uint32_t i = 0; i < users.Length(); i++)
    {
        Napi::String user_id = users.Get(i).As<Napi::String>();
        auto it = members_by_id.find(user_id.Utf8Value());

        if (it != members_by_id.end())
        {
            discord_members.Set(discord_members.Length(), it->second);
        } else {
            not_found.Set(not_found.Length(), user_id);
        }
    }

    Napi::Object result = Napi::Object::New(env);

    // result.Set("Yes", Napi::String::New(env, "sus"));
    // result.Set("your_obj", info[0]);
    result.Set("results", result_body);

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "process_op8"),
                Napi::Function::New(env, ProcessOP8));
    return exports;
}

NODE_API_MODULE(rfcnative, Init);
