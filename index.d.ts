export interface reqGuildMembersResults {
    results: {
        guild_id: string[],
        members: any[],
        not_found: string[],
        presences: any[],
    }
}

export interface reqGuildMembersArgs {
    discord_members: any[],
    user_ids: string[],
    guild_id: string[],
    presences: boolean,
    query: string,
}

export function processOP8(data: reqGuildMembersArgs): reqGuildMembersResults
