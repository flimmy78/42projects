/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 01:27:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/18 07:36:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

/*
** The various modes available for channels are as follows:
**
**        O - give "channel creator" status;
**        o - give/take channel operator privilege;
**        v - give/take the voice privilege;
**
**        a - toggle the anonymous channel flag;
**        i - toggle the invite-only channel flag;
**        m - toggle the moderated channel;
**        n - toggle the no messages to channel from clients on the
**            outside;
**        q - toggle the quiet channel flag;
**        p - toggle the private channel flag;
**        s - toggle the secret channel flag;
**        r - toggle the server reop channel flag;
**        t - toggle the topic settable by channel operator only flag;
**
**        k - set/remove the channel key (password);
**        l - set/remove the user limit to channel;
**
**        b - set/remove ban mask to keep users out;
**        e - set/remove an exception mask to override a ban mask;
**        I - set/remove an invitation mask to automatically override
**            the invite-only flag;
*/

/*
** User flags.
*/
# define USER_MODES "Oovira"

# define USR_CREATOR	0x0001
# define USR_CHANOP		0x0002
# define USR_VOICE		0x0004
# define USR_INVISIBL	0x0010
# define USR_RESTRICT	0x0020
# define USR_AWAY		0x0100
# define IRC_OPERATOR	0x1000

# define US_MODS1 USR_CREATOR, USR_CHANOP, USR_VOICE, USR_INVISIBL, USR_RESTRICT
# define US_MODS2 USR_AWAY

/*
** Channel flags.
*/
# define CHAN_MODES "aimnqpstkl"

# define CHFL_ANNON		0x0001
# define CHFL_INVITE	0x0002
# define CHFL_MOD		0x0004
# define CHFL_NOMSG		0x0010
# define CHFL_QUIET		0x0020
# define CHFL_PRIV		0x0040
# define CHFL_SECRET	0x0100
# define CHFL_TOPIC		0x0200
# define CHFL_KEY		0x0400
# define CHFL_LIMIT		0x1000

# define CH_MODS1 CHFL_ANNON, CHFL_INVITE, CHFL_MOD, CHFL_NOMSG, CHFL_QUIET
# define CH_MODS2 CHFL_PRIV, CHFL_SECRET, CHFL_TOPIC, CHFL_KEY, CHFL_LIMIT

#endif
