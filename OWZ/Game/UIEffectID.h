#pragma once

using UIEffectID = uint32_t;

//IDのタイプミス防止のため、よく使うIDは定数として定義しておきます
namespace UIEffectIDs
{
	const UIEffectID SelectEnter = Hash32("SelectEnter");
	const UIEffectID SelectExit = Hash32("SelectExit");
	const UIEffectID Decide = Hash32("Decide");
	const UIEffectID Cancel = Hash32("Cancel");
	const UIEffectID Show = Hash32("Show");
	const UIEffectID Hide = Hash32("Hide");
	const UIEffectID ValueAdjusted = Hash32("ValueAdjusted");
}