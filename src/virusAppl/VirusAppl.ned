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

package grid.virusAppl;
import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;

//
// network description file for your Veins Application. Add parameters here
//
simple VirusAppl extends BaseWaveApplLayer
{
	parameters:
		@class(VirusAppl);
		string appName = default("VirusAppl");
		int commStart = default(30);
		int infectStart = default(0);
		int infectStop = default(3600);
		double infectProb = default(0.10);
		bool patchingOn = default(false);
		bool regenPatchingOn = default(false);
		int commRadius @unit(m) = default(100m);
}