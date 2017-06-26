// Modified by Jacob Hultman, June 2017
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package vanet.virusAppl;

import vanet.statistics.StatisticsCollector;
import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;

simple VirusAppl extends BaseWaveApplLayer
{
	parameters:
		@class(VirusAppl);
		string appName = default("VirusAppl");
		
		@signal[numInfectedSignal](type="long");
		@statistic[numInfected](title="numInfected"; source="numInfectedSignal"; record=vector);
		
		@signal[fracInfectedSignal](type="double");
		@statistic[fracInfected](title="fracInfected"; source="fracInfectedSignal"; record=vector);
		
		@signal[ifInfectedSignal](type="long");
		@statistic[ifInfected](title="ifInfected"; source="ifInfectedSignal"; record=vector);
		
		double commStart = default(40);
		double infectStart = default(0);
		double infectStop = default(20);
		double infectRate = default(0.35);
		double patchStart = default(20);
		double patchStop = default(40);
		double patchRate = default(0.25);
		bool patchingOn = default(false);
		bool regenPatchingOn = default(false);
		double commRadius @unit(m) = default(300m);
		double commInterval @unit(s) = default(0.5s);
}